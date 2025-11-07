# Firmware


## Disco deck driver



Clone the [crazyflie-firmware](https://github.com/bitcraze/crazyflie-firmware) repository and add the driver for the disco deck ([disco.c](disco.c)) in [src/deck/drivers/src](https://github.com/bitcraze/crazyflie-firmware/tree/master/src/deck/drivers/src).

Also, add this line in [src/deck/drivers/src/Kbuild](https://github.com/bitcraze/crazyflie-firmware/blob/master/src/deck/drivers/src/Kbuild) to initialize the driver:
```
obj-y += disco.o
```

## Configure the firmware

Based on your platform, use its default configuration by running the following command:

#### Crazyflie 2.0, Crazyflie 2.1(+)
```
make cf2_defconfig
```
#### Crazyflie 2.1 Brushless
```
make cf21bl_defconfig
```
#### Crazyflie Bolt
```
make bolt_defconfig
```
Then, to force the deck driver, run this command:
```
make menuconfig
```
Navigate to **Expansion deck configuration → Deck discovery backends → Force load specified custom deck driver** and type "Disco".


## Build the firmware
Build the firmware on Linux by running this command:
```
make -j$(nproc)
```

## Flash the firmware

#### Manually entering bootloader mode

* Turn the Crazyflie off
* Start the Crazyflie in bootloader mode by pressing the power button for 3 seconds. Both the blue LEDs will blink.
* In your terminal, run
```
make cload
```

#### Automatically enter bootloader mode
* Make sure the Crazyflie is on
* In your terminal, run `CLOAD_CMDS="-w [CRAZYFLIE_URI]" make cload`
* or run `cfloader flash build/[BINARY_FILE] stm32-fw -w [CRAZYFLIE_URI]`
with [BINARY_FILE] being the binary file (**cf2.bin** for Crazyflie 2.x, **cf21bl.bin** for Crazyflie 2.1 Brushless etc.) and [CRAZYFLIE_URI] being the uri of the Crazyflie.


## Test the deck
After flasing the firmware to the Crazyflie and connecting to `cfclient`, the debug prints of the DiscoDeck should appear in the Console tab.

```
---
SYS: Crazyflie 2.1 is up and running!
SYS: Build 65:b300deabda4c (2025.09.1 +65) MODIFIED
SYS: I am 0x373732373433510800380021 and I have 1024KB of flash!
CFGBLK: v1, verification [OK]
DECK_DISCOVERY: Backend found: onewire
DECK_DISCOVERY: Backend found: forced
DECK_DISCOVERY: Backend found: deckctrl
DECK_FORCED: CONFIG_DECK_FORCE=Disco found
DECK_CORE: 1 deck(s) found
DECK_CORE: Calling INIT on driver Disco for deck 0
DiscoDeck: Initialize the Disco deck!
IMU: BMI088: Using I2C interface.
IMU: BMI088 Gyro connection [OK].
IMU: BMI088 Accel connection [OK]
IMU: BMP388 I2C connection [OK]
ESTIMATOR: Using Complementary (1) estimator
CONTROLLER: Using PID (1) controller
MTR-DRV: Using brushed motor driver
SYS: About to run tests in system.c.
SYS: NRF51 version: 2025.02 (CF21)
EEPROM: I2C connection [OK].
STORAGE: Storage check [OK].
IMU: BMI088 gyro self-test [OK]
DiscoDeck: Disco deck passed the test!
DECK_CORE: Deck 0 test [OK].
SYS: Self test passed!
STAB: Wait for sensor calibration...
SYS: Free heap: 17936 bytes
STAB: Starting stabilizer loop
```