ESP32 LEDC PWM Example
============================

Starts a FreeRTOS task to test the LEDC PWM.


### Build and upload

```bash
$ cd /path/to/12_ledc_pwm
$ make flash
```


### Connections


More details: http://wiki.jackslab.org/ESP32_PWM


### Try

After you upload the firmware into the flash, use a serial tool to check the output of the board:

```bash
$ picocom -b 115200 /dev/ttyUSB0
```



Serial will output:

```bash
```

See the README.md file in the upper level 'examples' directory for more information about examples.
