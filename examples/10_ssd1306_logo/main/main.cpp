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
 *
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

void drawColorBox(void)
{
	u8g_uint_t w, h;
	u8g_uint_t r, g, b;

	w = u8g.getWidth() / 32;
	h = u8g.getHeight() / 8;
	for (b = 0; b < 4; b++)
		for (g = 0; g < 8; g++)
			for (r = 0; r < 8; r++) {
				u8g.setColorIndex((r << 5) | (g << 2) | b);
				u8g.drawBox(g * w + b * w * 8, r * h, w, h);
			}
}

void drawLogo(uint8_t d)
{
	u8g.setFont(u8g_font_rajdhani_semibold32ptr);
	u8g.drawStr(15 + d, 26 + d, "Noduino");

	u8g.drawHLine(48 + d, 35 + d, 73);
	u8g.drawVLine(48 + d, 34 + d, 3);
}

void drawURL(void)
{
	u8g.setFont(u8g_font_4x6);
	u8g.drawStr(50, 48, "http://noduino.org");
}

void draw(void)
{
	if (u8g.getMode() == U8G_MODE_R3G3B2) {
		drawColorBox();
	}
	u8g.setColorIndex(1);
	if (U8G_MODE_GET_BITS_PER_PIXEL(u8g.getMode()) > 1) {
		drawLogo(2);
		u8g.setColorIndex(2);
		drawLogo(1);
		u8g.setColorIndex(3);
	}
	drawLogo(0);
	drawURL();
}

void ssd1306_task(void *pvParameter)
{
    while(1) {
		// picture loop
		u8g.firstPage();
		do {
			draw();
			u8g.setColorIndex(1);
		} while (u8g.nextPage());
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

extern "C" void app_main()
{
    nvs_flash_init();
    system_init();
	printf("Welcome to Noduino!\r\n");
	printf("Start to test SSD1306 OLED!\r\n");
    xTaskCreate(&ssd1306_task, "ssd1306_task", 1024, NULL, 5, NULL);
}
