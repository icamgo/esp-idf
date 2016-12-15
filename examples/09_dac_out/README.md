ESP32 DAC Example
============================

Starts a FreeRTOS task to output a voltage through GPIO25/26.

GPIO25/26 is D5/D6 in Quantum board

Use the ADC1_Channel7 (GPIO35) to measure the voltage. So you need use a wire
to connect the GPIO35 and D5/D6


### Build and upload

```bash
$ cd /path/to/09_dac_out
$ make flash
```


### Try

After you upload the firmware into the flash, use a serial tool to check the
output of the board:

```bash
$ picocom -b 115200 /dev/ttyUSB0
```


Serial will output:

```bash
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
ets Jun  8 2016 00:22:57

rst:0x10 (RTCWDT_RTC_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0x00
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:QIO, clock div:1
load:0x3ffc0008,len:4
load:0x3ffc000c,len:1880
load:0x40078000,len:3408
ho 0 tail 12 room 4
load:0x40080000,len:260
entry 0x40080034
I (370) heap_alloc_caps: Initializing heap allocator:
I (370) heap_alloc_caps: Region 19: 3FFB4784 len 0002B87C tag 0
I (372) heap_alloc_caps: Region 25: 3FFE8000 len 00018000 tag 1
I (382) cpu_start: Pro cpu up.
I (387) cpu_start: Single core mode
I (394) cpu_start: Pro cpu start user code
I (599) phy: phy_version: 258, Nov 29 2016, 15:51:07, 0, 0
I (748) cpu_start: Starting scheduler on PRO CPU.
Welcome to Noduino Quantum
Try to output a voltage through GPIO25/26... 
ESP32 ADC1_CH7 (IO35) = 229
ESP32 ADC1_CH7 (IO35) = 978
ESP32 ADC1_CH7 (IO35) = 1762
ESP32 ADC1_CH7 (IO35) = 2493
...
...

```

See the README.md file in the upper level 'examples' directory for more
information about examples.
