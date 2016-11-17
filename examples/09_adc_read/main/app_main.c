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
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include "nvs_flash.h"

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
	ADC1_ATTEN_0DB = 0,
	ADC1_ATTEN_3DB,
	ADC1_ATTEN_6DB,
	ADC1_ATTEN_12DB
};

uint32_t adc1_read(enum adc1_pad pad, enum adc1_atten att);


/* 
 * Read the amp adc, IO36 as the ADC_PRE_AMP
 * make sure connecting a 270pF cap from
 * esp32_pin5 to esp32_pin6
 */
uint32_t adc1_amp_read();

void read_adc1_task(void *pvParameters)
{
	while (1) {
		//printf("ESP32 RTCIO ADC PAD REG  = 0x%08X\n", *((uint32_t *)RTC_IO_ADC_PAD_REG));
		printf("ESP32 onchip ADC1 (IO36) = %d\n", adc1_read(ADC1_GPIO36, ADC1_ATTEN_12DB));
		printf("ESP32 onchip ADC1 (IO39) = %d\n", adc1_read(ADC1_GPIO39, ADC1_ATTEN_12DB));
		printf("ESP32 onchip ADC1 (IO34) = %d\n", adc1_read(ADC1_GPIO34, ADC1_ATTEN_12DB));
		printf("ESP32 onchip ADC1 (IO35) = %d\n", adc1_read(ADC1_GPIO35, ADC1_ATTEN_12DB));
		printf("ESP32 ADC PRE AMP (IO36) = %d\n\n", adc1_amp_read());
		vTaskDelay(4000 / portTICK_PERIOD_MS);
	}
}

void app_main()
{
	nvs_flash_init();
	system_init();
	printf("Welcome to Noduino Quantum\r\n");
	printf("Try to test the ADC1 pin of the ESP32 ... \r\n");
	xTaskCreatePinnedToCore(&read_adc1_task, "read_adc1_task", 1024, NULL, 5,
				NULL, 0);
}
