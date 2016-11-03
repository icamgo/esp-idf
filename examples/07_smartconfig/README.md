# Smartconfig Example

Starts a FreeRTOS task to enter smartconfig state:

```bash
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
ets Jun  8 2016 00:22:57

rst:0x10 (RTCWDT_RTC_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0x00
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3ffc0000,len:0
load:0x3ffc0000,len:920
load:0x40078000,len:2836
ho 0 tail 12 room 4
load:0x40098000,len:692
entry 0x4009813c
I (94) heap_alloc_caps: Initializing heap allocator:
I (94) heap_alloc_caps: Region 19: 3FFC0FF0 len 0001F010 tag 0
I (95) heap_alloc_caps: Region 25: 3FFE8000 len 00018000 tag 1
I (105) cpu_start: Pro cpu up.
I (111) cpu_start: Single core mode
I (117) cpu_start: Pro cpu start user code
rtc v112 Sep 26 2016 22:32:10
XTAL 40M
I (156) cpu_start: Starting scheduler on PRO CPU.
frc2_timer_task_hdl:3ffc4608, prio:22, stack:2048
tcpip_task_hdlxxx : 3ffc5228, prio:18,stack:2048
phy_version: 123, Sep 13 2016, 20:01:58, 0
pp_task_hdl : 3ffc8b2c, prio:23, stack:8192
mode : sta(24:0a:c4:01:cd:6c)
Welcome to Noduino Quantum
Smartconfig is comming... 
SC version: V2.6.2
[sc_system_init_done,466]
[sc_wifi_scan_done,297] STATUS:0
[sc_system_init_done,466]
[sc_wifi_scan_done,297] STATUS:0
ic_enable_sniffer
[sc_wifi_scan_done,435] STATUS:0
SC_STATUS_FIND_CHANNEL
TYPE: AIRKISS
T|PHONE MAC: 90 fd 60 3c c5 5d
T|AP MAC   : e0 46 9a 8b 84 7e
SC_STATUS_GETTING_SSID_PSWD
SC_TYPE:SC_TYPE_AIRKISS
T|pswd : maikelab 
T|ssid : Noduino-AP
ic_disable_sniffer
SC_STATUS_LINK
n:11 0, o:1 0, ap:255 255, sta:11 0, prof:1
state: 0 -> 2 (b0)
state: 2 -> 3 (0)
state: 3 -> 5 (10)
add 0

connected with Noduino-AP, channel 11
I (158305) event: ip: 192.168.1.99, mask: 255.255.255.0, gw: 192.168.1.1
SC_STATUS_LINK_OVER
```


See the README.md file in the upper level 'examples' directory for more information about examples.
