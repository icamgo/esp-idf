ESP32 Onchip Sensor Example
============================

Starts a FreeRTOS task to read the hall and temperature sensor inside the esp32 chip.


### Build and upload

```bash
$ cd /path/to/09_onchip_sensor
$ make flash
```


### Try

After you upload the firmware into the flash, use a serial tool to check the output of the board:

```bash
$ picocom -b 115200 /dev/ttyUSB0
```


Serial will output:

```bash
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
ets Jun  8 2016 00:22:57

rst:0x10 (RTCWDT_RTC_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0x00
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:QIO, clock div:1
load:0x3ffc0000,len:0
load:0x3ffc0000,len:920
load:0x40078000,len:3220
ho 0 tail 12 room 4
load:0x40080000,len:260
entry 0x40080034
I (63) heap_alloc_caps: Initializing heap allocator:
I (63) heap_alloc_caps: Region 19: 3FFB45D8 len 0002BA28 tag 0
I (65) heap_alloc_caps: Region 25: 3FFE8000 len 00018000 tag 1
I (74) cpu_start: Pro cpu up.
I (80) cpu_start: Single core mode
I (86) cpu_start: Pro cpu start user code
rtc v118 Oct 19 2016 15:22:11
XTAL 40M
I (121) cpu_start: Starting scheduler on PRO CPU.
Welcome to Noduino Quantum
Try to read the temperature sensor of the ESP32 onchip ... 
ESP32 onchip Temperature = 143
ESP32 onchip Hall sensor = 5247
ESP32 onchip Temperature = 145
ESP32 onchip Hall sensor = 5240

```

See the README.md file in the upper level 'examples' directory for more information about examples.
