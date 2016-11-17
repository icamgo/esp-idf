ESP32 ADC read Example
============================

Starts a FreeRTOS task to read the adc1 and adc2 inside the esp32 chip.


### Build and upload

```bash
$ cd /path/to/09_adc_read
$ make flash
```


### Try

After you upload the firmware into the flash, use a serial tool to check the output of the board:

```bash
$ picocom -b 115200 /dev/ttyUSB0
```

Connect the Quantum_IO35 to 3V3 (measure the power voltage)
Connect the Quantum_IO34 to GND (measure the GND voltage)
Connect the Quantum_IO36 to GND


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
I (64) heap_alloc_caps: Region 25: 3FFE8000 len 00018000 tag 1
I (74) cpu_start: Pro cpu up.
I (80) cpu_start: Single core mode
I (86) cpu_start: Pro cpu start user code
rtc v118 Oct 19 2016 15:22:11
XTAL 40M
I (121) cpu_start: Starting scheduler on PRO CPU.
Welcome to Noduino Quantum
Try to test the ADC1 pin of the ESP32 ... 
ESP32 onchip ADC1 (IO36) = 0
ESP32 onchip ADC1 (IO39) = 0
ESP32 onchip ADC1 (IO34) = 0
ESP32 onchip ADC1 (IO35) = 4095
ESP32 ADC PRE AMP (IO36) = 0

ESP32 onchip ADC1 (IO36) = 0
ESP32 onchip ADC1 (IO39) = 0
ESP32 onchip ADC1 (IO34) = 0
ESP32 onchip ADC1 (IO35) = 4095
ESP32 ADC PRE AMP (IO36) = 0
......
......

```

See the README.md file in the upper level 'examples' directory for more information about examples.
