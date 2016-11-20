ESP32 dust sensor example
============================

Starts a FreeRTOS task to read the Sharp GP2Y1010AU0F Particle Sensor.


### Build and upload

```bash
$ cd /path/to/11_sharp_dust
$ make flash
```


### Connections

Sharp pin 1 (V-LED)   => 150ohm resister => Quantum_VIN_3V3
Sharp pin 2 (LED-GND) => Quantum_GND
Sharp pin 3 (LED)     => Quantum_D8_IO22
Sharp pin 4 (S-GND)   => Quantum_GND
Sharp pin 5 (Vo)      => Quantum_IO35
Sharp pin 6 (Vcc)     => Quantum_VIN_3V3

More details: http://wiki.jackslab.org/ESP32_Partical


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
load:0x3ffc0008,len:0
load:0x3ffc0008,len:1964
load:0x40078000,len:3648
ho 0 tail 12 room 4
load:0x40080000,len:256
entry 0x40080034
I (243) heap_alloc_caps: Initializing heap allocator:
I (243) heap_alloc_caps: Region 19: 3FFB1AFC len 0002E504 tag 0
I (244) heap_alloc_caps: Region 25: 3FFE8000 len 00018000 tag 1
I (254) cpu_start: Pro cpu up.
I (260) cpu_start: Single core mode
I (266) cpu_start: Pro cpu start user code
rtc v118 Oct 19 2016 15:22:11
XTAL 40M
I (302) cpu_start: Starting scheduler on PRO CPU.
Welcome to Noduino Quantum
Sharp GP2Y1010AU0F Particle Sensor Example... 
Sharp GP2Y1010AU0F Particle Sensor Example... 
Partical voltage = 0.49V
Partical voltage = 0.49V
Partical voltage = 0.64V
Partical voltage = 0.57V
Partical voltage = 0.58V
Partical voltage = 0.51V
Partical voltage = 0.57V
Partical voltage = 0.60V
Partical voltage = 0.56V
Partical voltage = 0.58V
Partical voltage = 0.54V
Partical voltage = 0.47V
Partical voltage = 0.67V
Partical voltage = 0.57V
......
......
```

See the README.md file in the upper level 'examples' directory for more information about examples.
