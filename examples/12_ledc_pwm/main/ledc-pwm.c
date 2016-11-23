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
#include "driver/ledc.h"
#include "driver/periph_ctrl.h"

inline void delay_ms(int ms)
{
	vTaskDelay(ms / portTICK_PERIOD_MS);
}

inline void delay_us(int us)
{
	ets_delay_us(us);
}

void ledc_init()
{
	//enable LEDC module, or you can not set any register of it.
	periph_module_enable(PERIPH_LEDC_MODULE);
	
	ledc_timer_config_t timer_conf = {
		.bit_num = LEDC_TIMER_12_BIT,			//set timer counter bit number
		.freq_hz = 1000,						//set frequency of pwm, here, 1000Hz
		.speed_mode = LEDC_HIGH_SPEED_MODE,		//timer mode,
		.timer_num = LEDC_TIMER_0				//timer number
	};
	ledc_timer_config(&timer_conf);				//setup timer.

	ledc_channel_config_t ledc_conf = {
		.channel = LEDC_CHANNEL_0,			//set LEDC channel0
		.duty = 1000,						//set the duty for initialization.(duty range is 0 ~ ((2**bit_num)-1)
		.gpio_num = 27,						//GPIO number
		.intr_type = LEDC_INTR_FADE_END,	//GPIO INTRTYPE, as anexample,we enable fade_end interrupt here.
		.speed_mode = LEDC_HIGH_SPEED_MODE,	//set LEDC mode,from ledc_mode_t
		.timer_sel = LEDC_TIMER_0			//set LEDC timer source, if different channel use one timer,
	};
	ledc_channel_config(&ledc_conf);		//setup the configuration

	ledc_conf.channel = LEDC_CHANNEL_1;		//set LEDC channel0
	ledc_conf.gpio_num = 26;				//GPIO number
	ledc_channel_config(&ledc_conf);		//setup the configuration

	ledc_conf.channel = LEDC_CHANNEL_2;		//set LEDC channel0
	ledc_conf.gpio_num = 25;				//GPIO number
	ledc_channel_config(&ledc_conf);		//setup the configuration

	ledc_conf.channel = LEDC_CHANNEL_3;		//set LEDC channel0
	ledc_conf.gpio_num = 4;					//GPIO number
	ledc_channel_config(&ledc_conf);		//setup the configuration
}

void update_ch0()
{
	uint32_t ledc_channel = LEDC_CHANNEL_0;				//LEDC channel(0-73)
	uint32_t duty = 2000;								//duty range is 0 ~ ((2**bit_num)-1)

	ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel, duty);	//set speed mode, channel, and duty.

	//after set duty, we need to call ledc_update_duty to update the settings.
	ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel);
}

void ledc_pwm_task(void *pvParameters)
{
	while (1) {
		update_ch0();
		delay_ms(4000);
	}
}

void app_main()
{
	nvs_flash_init();

	ledc_init();

	printf("Welcome to Noduino Quantum\r\n");
	printf("LEDC PWM Example... \r\n");
	xTaskCreatePinnedToCore(&ledc_pwm_task, "ledc_pwm_task", 1024, NULL, 5,
				NULL, 0);
}
