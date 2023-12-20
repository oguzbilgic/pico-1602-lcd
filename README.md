# Pi Pico 1602A LCD

This project is a simple LCD driver for the Raspberry Pi Pico. It is written in C and uses the Pico's GPIO pins to interface with the LCD.

## Functions

- `init_pins()`: This function initializes the GPIO pins that will be used to interface with the LCD. Pins 3 to 5 are used for RS, RW, and EN respectively. Pins 6 to 13 are used as data pins.

- `set_rs_rw(uint8_t rs, uint8_t rw)`: This function sets the RS and RW pins. RS is connected to GPIO pin 3 and RW to GPIO pin 4.

- `pulse_enable()`: This function pulses the enable pin (GPIO pin 5) to signal the LCD that data is ready to be read.

- `set_data_pins(uint8_t data)`: This function sets the data pins (GPIO pins 6 to 13) according to the 8 bits of the input data.

- `write_data(uint8_t data)`: This function writes data to the LCD. It sets the RS pin to 1 and the RW pin to 0, then sets the data pins and pulses the enable pin.

## Dependencies

This project depends on the `pico/stdlib.h` library for the Raspberry Pi Pico.

### Building

```bash
mkdir build
cd build
cmake ..
make
```

This will create a `.uf2` file in your build directory.

### Flashing

1. Connect your Raspberry Pi Pico to your computer while holding the BOOTSEL button. This will put it in bootloader mode.
2. The Pico will appear as a mass storage device on your computer.
3. Drag and drop the `.uf2` file onto the Pico. The Pico will automatically reboot and start running your code.