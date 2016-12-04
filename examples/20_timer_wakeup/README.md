ESP32 Timer Expire Wakeup from Deep Sleep Example
==================================================

### Build and upload

```bash
$ cd /path/to/20_timer_wakeup
$ make flash
```


### Try

After you upload the firmware into the flash, use a serial tool to check the output of the board:

```bash
$ picocom -b 115200 /dev/ttyUSB0
```


Serial will output:

```bash
rst:0x5 (DEEPSLEEP_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0x00
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:QIO, clock div:1
load:0x3ffc0008,len:0
load:0x3ffc0008,len:1964
load:0x40078000,len:3668
load:0x40080000,len:260
entry 0x40080034
I (261) heap_alloc_caps: Initializing heap allocator:
I (261) heap_alloc_caps: Region 19: 3FFB4760 len 0002B8A0 tag 0
I (263) heap_alloc_caps: Region 25: 3FFE8000 len 00018000 tag 1
I (273) cpu_start: Pro cpu up.
I (279) cpu_start: Single core mode
I (285) cpu_start: Pro cpu start user code
I (310) rtc: rtc v160 Nov 22 2016 19:00:05
I (318) rtc: XTAL 40M
I (374) phy: phy_version: 258, Nov 29 2016, 15:51:07, 0, 1
I (374) cpu_start: Starting scheduler on PRO CPU.
Welcome to Noduino Quantum
Try to investigate the ULP/RTC of ESP32 ... 
```

LED (connect to GPIO27) flash two times, then enter deep sleep

ESP32 will be waked up after 8 seconds ...

