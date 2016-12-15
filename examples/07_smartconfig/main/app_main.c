/*
 *  MaiKe Labs (2016 - 2026)
 *
 *  Written by Jack Tan <jiankemeng@gmail.com>
 *
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *  
 *    http://www.apache.org/licenses/LICENSE-2.0
 *  
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 *  under the License.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_smartconfig.h"
#include "esp_system.h"
#include "nvs_flash.h"

void smartconfig_done(smartconfig_status_t status, void *pdata)
{
	switch (status) {
	case SC_STATUS_WAIT:
		printf("SC_STATUS_WAIT\n");
		break;
	case SC_STATUS_FIND_CHANNEL:
		printf("SC_STATUS_FIND_CHANNEL\n");
		break;
	case SC_STATUS_GETTING_SSID_PSWD:
		printf("SC_STATUS_GETTING_SSID_PSWD\n");
		smartconfig_type_t *type = pdata;
		if (*type == SC_TYPE_ESPTOUCH) {
			printf("SC_TYPE:SC_TYPE_ESPTOUCH\n");
		} else {
			printf("SC_TYPE:SC_TYPE_AIRKISS\n");
		}
		break;
	case SC_STATUS_LINK:
		printf("SC_STATUS_LINK\n");
		wifi_config_t wifi_config;
		wifi_config.sta = *((wifi_sta_config_t *)pdata);
		esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

		esp_wifi_disconnect();
		esp_wifi_connect();
		break;
	case SC_STATUS_LINK_OVER:
		printf("SC_STATUS_LINK_OVER\n");
		if (pdata != NULL) {
			uint8_t phone_ip[4] = { 0 };

			memcpy(phone_ip, (uint8_t *) pdata, 4);
			printf("Phone ip: %d.%d.%d.%d\n", phone_ip[0],
			       phone_ip[1], phone_ip[2], phone_ip[3]);
		}
		esp_smartconfig_stop();
		break;
	}

}

void smartconfig_task(void *pvParameters)
{
	esp_smartconfig_start(smartconfig_done);

	while (1) {
		vTaskDelay(6000 / portTICK_PERIOD_MS);
	}
}

static esp_err_t event_handler(void *ctx, system_event_t * event)
{
	return 0;
}

static void smartconfig_init(void)
{
	tcpip_adapter_init();
	esp_event_loop_init(event_handler, NULL);
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	esp_wifi_init(&cfg);

	//SC_TYPE_ESPTOUCH,SC_TYPE_AIRKISS,SC_TYPE_ESPTOUCH_AIRKISS
	esp_smartconfig_set_type(SC_TYPE_AIRKISS);

	esp_wifi_set_mode(WIFI_MODE_STA);
	esp_wifi_start();
}

void app_main()
{
	nvs_flash_init();
	smartconfig_init();
	printf("Welcome to Noduino Quantum\r\n");
	printf("Smartconfig is comming... \r\n");
	xTaskCreatePinnedToCore(&smartconfig_task, "smartconfig_task", 2048,
				NULL, 5, NULL, 0);
}
