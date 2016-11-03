/*
 *  Copyright (c) 2016 - 2026 MaiKe Labs
 *
 *  Interface for noduino and the SSD1306 chip (SOLOMON) variant 
 *  I2C protocol 
 * 
 *  Special pin usage:
 *    U8G_PI_I2C_OPTION additional options
 *    U8G_PI_A0_STATE   used to store the last value of the command/data register selection
 *    U8G_PI_SET_A0     1: Signal request to update I2C device with new A0_STATE
 *                      0: Do nothing, A0_STATE matches I2C device
 *    U8G_PI_RESET      reset line
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "u8g.h"
#include "driver/gpio.h"
#include "rom/gpio.h"
#include "rom/ets_sys.h"

#define I2C_SLA			0x3C		// The i2c address of SSD1306
#define I2C_CMD_MODE	0x000
#define I2C_DATA_MODE	0x040

#define I2C_MASTER_SDA_GPIO (pinSDA)
#define I2C_MASTER_SCL_GPIO (pinSCL)

#define I2C_MASTER_SDA_HIGH_SCL_HIGH()  \
	gpio_output_set(1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

#define I2C_MASTER_SDA_HIGH_SCL_LOW()  \
    gpio_output_set(1<<I2C_MASTER_SDA_GPIO, 1<<I2C_MASTER_SCL_GPIO, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

#define I2C_MASTER_SDA_LOW_SCL_HIGH()  \
    gpio_output_set(1<<I2C_MASTER_SCL_GPIO, 1<<I2C_MASTER_SDA_GPIO, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

#define I2C_MASTER_SDA_LOW_SCL_LOW()  \
    gpio_output_set(0, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 1<<I2C_MASTER_SDA_GPIO | 1<<I2C_MASTER_SCL_GPIO, 0)

////////////////////////////////////////////
static uint8_t m_nLastSDA;
static uint8_t m_nLastSCL;

static uint8_t pinSDA = 22;
static uint8_t pinSCL = 21;

#define i2c_wait    ets_delay_us

static void i2c_set_dc(uint8_t SDA, uint8_t SCL)
{
	SDA &= 0x01;
	SCL &= 0x01;
	m_nLastSDA = SDA;
	m_nLastSCL = SCL;

	if ((0 == SDA) && (0 == SCL)) {
		I2C_MASTER_SDA_LOW_SCL_LOW();
	} else if ((0 == SDA) && (1 == SCL)) {
		I2C_MASTER_SDA_LOW_SCL_HIGH();
	} else if ((1 == SDA) && (0 == SCL)) {
		I2C_MASTER_SDA_HIGH_SCL_LOW();
	} else {
		I2C_MASTER_SDA_HIGH_SCL_HIGH();
	}
}

void i2c_stop(void)
{
	i2c_wait(5);

	i2c_set_dc(0, m_nLastSCL);
	i2c_wait(5);	// sda 0
	i2c_set_dc(0, 1);
	i2c_wait(5);	// sda 0, scl 1
	i2c_set_dc(1, 1);
	i2c_wait(5);	// sda 1, scl 1
}

void i2c_init(void)
{
	uint8_t i;

	i2c_set_dc(1, 0);
	i2c_wait(5);

	// when SCL = 0, toggle SDA to clear up
	i2c_set_dc(0, 0);
	i2c_wait(5);
	i2c_set_dc(1, 0);
	i2c_wait(5);

	// set data_cnt to max value
	for (i = 0; i < 28; i++) {
		i2c_set_dc(1, 0);
		i2c_wait(5);	// sda 1, scl 0
		i2c_set_dc(1, 1);
		i2c_wait(5);	// sda 1, scl 1
	}

	// reset all
	i2c_stop();
	return;
}

void i2c_gpio_init(uint8_t sda, uint8_t scl)
{
	pinSDA = sda;
	pinSCL = scl;

	//pinMode(pinSDA, INPUT_PULLUP);
	//pinMode(pinSCL, INPUT_PULLUP);
	gpio_pad_select_gpio(pinSDA);
	gpio_set_direction(pinSDA, GPIO_MODE_INPUT);
	gpio_set_pull_mode(pinSDA, GPIO_PULLUP_ONLY);
	gpio_pad_select_gpio(pinSCL);
	gpio_set_direction(pinSCL, GPIO_MODE_INPUT);
	gpio_set_pull_mode(pinSCL, GPIO_PULLUP_ONLY);

	I2C_MASTER_SDA_HIGH_SCL_HIGH();

	i2c_init();
}

void i2c_start(void)
{
	i2c_set_dc(1, m_nLastSCL);
	i2c_wait(5);
	i2c_set_dc(1, 1);
	i2c_wait(5);	// sda 1, scl 1
	i2c_set_dc(0, 1);
	i2c_wait(5);	// sda 0, scl 1
}

static uint8_t i2c_get_dc(void)
{
	uint8_t sda_out;
	sda_out = GPIO_INPUT_GET(GPIO_ID_PIN(I2C_MASTER_SDA_GPIO));
	return sda_out;
}

uint8_t i2c_get_ack(void)
{
	uint8_t retVal;
	i2c_set_dc(m_nLastSDA, 0);
	i2c_wait(5);
	i2c_set_dc(1, 0);
	i2c_wait(5);
	i2c_set_dc(1, 1);
	i2c_wait(5);

	retVal = i2c_get_dc();
	i2c_wait(5);
	i2c_set_dc(1, 0);
	i2c_wait(5);

	return retVal;
}

void i2c_write_byte(uint8_t wrdata)
{
	uint8_t dat;
	int8_t i;

	i2c_wait(5);

	i2c_set_dc(m_nLastSDA, 0);
	i2c_wait(5);

	for (i = 7; i >= 0; i--) {
		dat = wrdata >> i;
		i2c_set_dc(dat, 0);
		i2c_wait(5);
		i2c_set_dc(dat, 1);
		i2c_wait(5);

		if (i == 0) {
			i2c_wait(3);	////
		}

		i2c_set_dc(dat, 0);
		i2c_wait(5);
	}
}

////////////////////////////////////////////
static uint32_t platform_i2c_setup(uint8_t sda, uint8_t scl)
{
	i2c_gpio_init(sda, scl);
	return 0;
}

static void platform_i2c_send_start()
{
	i2c_start();
}

static void platform_i2c_send_stop()
{
	i2c_stop();
}

static int platform_i2c_send_address(uint16_t address)
{
	// Convert enum codes to R/w bit value.
	// If TX == 0 and RX == 1, this test will be removed by the compiler

	i2c_write_byte((uint8_t) ((address << 1) | 0));
	// Low-level returns nack (0=acked); we return ack (1=acked).
	return !i2c_get_ack();
}

int platform_i2c_send_byte(uint8_t data)
{
	i2c_write_byte(data);
	// Low-level returns nack (0=acked); we return ack (1=acked).
	return !i2c_get_ack();
}

static uint8_t do_i2c_start(uint8_t sla)
{
	platform_i2c_send_start();

	// ignore return value -> tolerate missing ACK
	platform_i2c_send_address(sla);

	return 1;
}

static uint8_t u8g_com_esp8266_ssd_start_sequence(u8g_t * u8g)
{
	/* are we requested to set the a0 state? */
	if (u8g->pin_list[U8G_PI_SET_A0] == 0)
		return 1;

	/* setup bus, might be a repeated start */
	if (do_i2c_start(I2C_SLA) == 0)
		return 0;
	if (u8g->pin_list[U8G_PI_A0_STATE] == 0) {
		// ignore return value -> tolerate missing ACK
		if (platform_i2c_send_byte(I2C_CMD_MODE) == 0) ;	//return 0;
	} else {
		platform_i2c_send_byte(I2C_DATA_MODE);
	}

	u8g->pin_list[U8G_PI_SET_A0] = 0;
	return 1;
}

uint8_t u8g_com_esp8266_ssd_i2c_fn(u8g_t * u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
	switch (msg) {
	case U8G_COM_MSG_INIT:
		// we assume that the i2c bus was already initialized
		//u8g_i2c_init(u8g->pin_list[U8G_PI_I2C_OPTION]);
		platform_i2c_setup(22, 21);
		break;

	case U8G_COM_MSG_STOP:
		break;

	case U8G_COM_MSG_RESET:
		/* Currently disabled, but it could be enable. Previous restrictions have been removed */
		gpio_set_level(4, arg_val);
		break;

	case U8G_COM_MSG_CHIP_SELECT:
		u8g->pin_list[U8G_PI_A0_STATE] = 0;
		u8g->pin_list[U8G_PI_SET_A0] = 1;	/* force a0 to set again, also forces start condition */
		if (arg_val == 0) {
			/* disable chip, send stop condition */
			platform_i2c_send_stop();
		} else {
			/* enable, do nothing: any byte writing will trigger the i2c start */
		}
		break;

	case U8G_COM_MSG_WRITE_BYTE:
		//u8g->pin_list[U8G_PI_SET_A0] = 1;
		if (u8g_com_esp8266_ssd_start_sequence(u8g) == 0)
			return platform_i2c_send_stop(), 0;
		// ignore return value -> tolerate missing ACK
		if (platform_i2c_send_byte(arg_val) == 0) ;
		break;

	case U8G_COM_MSG_WRITE_SEQ:
	case U8G_COM_MSG_WRITE_SEQ_P:
		//u8g->pin_list[U8G_PI_SET_A0] = 1;
		if (u8g_com_esp8266_ssd_start_sequence(u8g) == 0)
			return platform_i2c_send_stop(), 0;
		{
			register uint8_t *ptr = arg_ptr;
			while (arg_val > 0) {
				// ignore return value -> tolerate missing ACK
				if (platform_i2c_send_byte(*ptr++) == 0) ;
				arg_val--;
			}
		}
		break;

	case U8G_COM_MSG_ADDRESS:	/* define cmd (arg_val = 0) or data mode (arg_val = 1) */
		u8g->pin_list[U8G_PI_A0_STATE] = arg_val;
		u8g->pin_list[U8G_PI_SET_A0] = 1;	/* force a0 to set again */

		break;
	}
	return 1;
}

uint8_t u8g_com_esp8266_hw_spi_fn(u8g_t * u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
	return 1;
}
