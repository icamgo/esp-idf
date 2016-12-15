/*
 * MaiKe Labs (2016 - 2026)
 *
 * Written by Jack Tan <jiankemeng@gmail.com>
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/rtc_io_reg.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

enum adc1_pad { 
	ADC1_GPIO36 = 0,
	ADC1_GPIO37,
	ADC1_GPIO38,
	ADC1_GPIO39, 
	ADC1_GPIO32,
	ADC1_GPIO33,
	ADC1_GPIO34,
	ADC1_GPIO35 
};
 
enum adc1_atten {
	ADC1_ATTEN_0DB = 0,     /* 0 ~ 1V can be measured */
	ADC1_ATTEN_3DB,         /* 0 ~ 1.4V can be measured */
	ADC1_ATTEN_6DB,         /* 0 ~ 2V can be measured */
	ADC1_ATTEN_12DB         /* 0 ~ 4V can be measured */
};

uint32_t adc1_read(enum adc1_pad pad, enum adc1_atten att);


/* 
 * Read the amp adc, IO36 as the ADC_PRE_AMP
 * make sure connecting a 270pF cap from
 * esp32_pin5 to esp32_pin6
 */
uint32_t adc1_amp_read();

inline void delay_ms(int ms)
{
	vTaskDelay(ms / portTICK_PERIOD_MS);
}

inline void delay_us(int us)
{
	ets_delay_us(us);
}

void sharp_init()
{

    /*
	 * Configure the IOMUX register for GPIO 22 (some pads are
     * muxed to GPIO on reset already, but some default to other
     * functions and need to be switched to GPIO. Consult the
     * Technical Reference for a list of pads and their default
     * functions.)
    */
    gpio_pad_select_gpio(22);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(22, GPIO_MODE_OUTPUT);

	/* power off the led of partical sensor */
	gpio_set_level(22, 1);
}

float get_sharp()
{
	float dust_vo = 0;

	gpio_set_level(22, 0); // power on the LED
	delay_us(280);

	// read the dust value via ADC1 GPIO35 pin
	dust_vo = adc1_read(ADC1_GPIO35, ADC1_ATTEN_12DB) / 4096.0 * 4.0;

	//dust_val = adc1_amp_read();
	delay_us(40);

	gpio_set_level(22, 1); // turn the LED off
	delay_us(9680);
	   
	return dust_vo;
}

void read_partical_task(void *pvParameters)
{
	while (1) {
		//printf("ESP32 ADC PRE AMP (IO36) = %d\n\n", adc1_amp_read());
		printf("Partical voltage = %2.2fV\n", get_sharp());
		vTaskDelay(8000 / portTICK_PERIOD_MS);
	}
}

void app_main()
{
	nvs_flash_init();

	sharp_init();

	printf("Welcome to Noduino Quantum\r\n");
	printf("Sharp GP2Y1010AU0F Particle Sensor Example... \r\n");
	xTaskCreatePinnedToCore(&read_partical_task, "read_partical_task", 2048, NULL, 5,
				NULL, 0);
}
