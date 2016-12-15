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
#include "soc/sens_reg.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "driver/adc.h"

/* 
 * Read the amp adc, IO36 as the ADC_PRE_AMP
 * make sure connecting a 270pF cap from
 * esp32_pin5 to esp32_pin6
 */
//uint32_t adc1_amp_read();

void read_adc_task(void *pvParameters)
{
	while (1) {
		printf("----------------------------------------------\n");
		printf("ESP32 ADC1_CH0 (IO36) = %d\n", adc1_get_voltage(ADC1_CHANNEL_0));
		printf("ESP32 ADC1_CH1 (IO39) = %d\n", adc1_get_voltage(ADC1_CHANNEL_1));
		printf("ESP32 ADC1_CH6 (IO34) = %d\n", adc1_get_voltage(ADC1_CHANNEL_6));
		printf("ESP32 ADC1_CH7 (IO35) = %d\n", adc1_get_voltage(ADC1_CHANNEL_7));

		vTaskDelay(4000 / portTICK_PERIOD_MS);
	}
}

void adc1_init()
{
	adc1_config_width(ADC_WIDTH_12Bit);

	adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_0db);
	adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_0db);
	adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_0db);
	adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_0db);
}

void app_main()
{
	nvs_flash_init();
	adc1_init();

	printf("Welcome to Noduino Quantum\r\n");
	printf("Try to test the ADC1 pin of the ESP32 ... \r\n");
	xTaskCreatePinnedToCore(&read_adc_task, "read_adc_task", 2048, NULL, 5,
				NULL, 0);
}
