SSD1306 OLED screen Example
===========================

Show a picture logo in the SSD1306 OLED screen


### Pin connection

*  Connect VCC of the SSD1306 OLED to 3.3V
*  Connect GND to Ground
*  Connect SCL to i2c clock - GPIO21
*  Connect SDA to i2c data  - GPIO22
*	Connect DC to GND (The scanned i2c address is 0x3C)


### Build and upload

```bash
$ cd /path/to/10_ssd1306_logo
$ make flash
```

See the README.md file in the upper level 'examples' directory for more information about examples.
