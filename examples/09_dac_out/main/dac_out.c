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
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "driver/dac.h"
#include "driver/adc.h"

void dac_out_task(void *pvParameters)
{
	static uint8_t i = 0;
	while (1) {
		dac_out_voltage(DAC_CHANNEL_1, i%256);
		dac_out_voltage(DAC_CHANNEL_2, (i + 20)%256);

		i += 50;

		printf("ESP32 ADC1_CH7 (IO35) = %d\n", adc1_get_voltage(ADC1_CHANNEL_7));
		vTaskDelay(4000 / portTICK_PERIOD_MS);
	}
}

void app_main()
{
	nvs_flash_init();

	adc1_config_width(ADC_WIDTH_12Bit);
	adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_11db);

	printf("Welcome to Noduino Quantum\r\n");
	printf("Try to output a voltage through GPIO25/26... \r\n");
	xTaskCreatePinnedToCore(&dac_out_task, "dac_out_task", 2048, NULL, 5,
				NULL, 0);
}
