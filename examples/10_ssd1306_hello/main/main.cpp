/*
 *  MaiKe Labs (2016 - 2026)
 *
 *  Written by Jack Tan <jiankemeng@gmail.com>
 *
 *  Connect VCC of the SSD1306 OLED to 3.3V
 *  Connect GND to Ground
 *  Connect SCL to i2c clock - GPIO21
 *  Connect SDA to i2c data  - GPIO22
 *	Connect DC to GND (The scanned i2c address is 0x3C)
 *
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

void draw(void)
{
	u8g.setFont(u8g_font_unifont);
	u8g.drawStr(0, 22, "Hello World!");
}

void ssd1306_task(void *pvParameter)
{
	// assign default color value
	if (u8g.getMode() == U8G_MODE_R3G3B2) {
		u8g.setColorIndex(255);	// white
	} else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
		u8g.setColorIndex(3);	// max intensity
	} else if (u8g.getMode() == U8G_MODE_BW) {
		u8g.setColorIndex(1);	// pixel on
	} else if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}

    while(1) {
		// picture loop
		u8g.firstPage();
		do {
			draw();
		} while (u8g.nextPage());
		draw();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

extern "C" void app_main()
{
    nvs_flash_init();
	printf("Welcome to Noduino!\r\n");
	printf("Start to test SSD1306 OLED!\r\n");
    xTaskCreate(&ssd1306_task, "ssd1306_task", 2048, NULL, 5, NULL);
}
