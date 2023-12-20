#include "pico/stdlib.h"
#include <stdio.h>
#include <stdint.h>

// initialize gpio pins
void init_pins() {
    // rs, rw, and en are all outputs
    for (int i = 3; i < 6; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }

    // loop from 6 to 14 
    for (int i = 6; i < 14; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }
}

void set_rs_rw(uint8_t rs, uint8_t rw) {
    gpio_put(3, rs);
    gpio_put(4, rw);
}

void pulse_enable() {
    static uint16_t DELAY = 600;

    sleep_us(DELAY);
    gpio_put(5, 1);
    sleep_us(DELAY);
    gpio_put(5, 0);
    sleep_us(DELAY);
}

void set_data_pins(uint8_t data) {
    // loop over each bit in the data
    for (int i = 0; i < 8; i++) {
        // set the data pin to the current bit
        gpio_put(6 + i, data & (1 << i));
    }
}

void write_data(uint8_t data) {
    set_rs_rw(1, 0);

    set_data_pins(data);

    pulse_enable();
    printf("Write: %x\n", data);
}

void send_data(uint8_t data) {
    set_rs_rw(0, 0);

    set_data_pins(data);
    
    pulse_enable();
    printf("Send: %x\n", data);

    sleep_ms(6);
}

int main() {
    const uint LED_PIN = 25;

    // Initialize the Pico SDK
    stdio_init_all();

    // Set the LED pin as an output
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    init_pins();

    sleep_ms(4000);

    // set 4 bit mode
    // send_data(0x30);
    // send_data(0x30);
    // send_data(0x30);

    // send_data(0x20);

    // set function
    // send_data(0x20);
    // send_data(0xc0);

    // clear display
    send_data(0x00);
    send_data(0x10);

    // return home
    send_data(0x00);
    send_data(0x20);

    // display on
    send_data(0x00);
    send_data(0xc0);
    


    while (1) {
        // Toggle the LED state
        gpio_put(LED_PIN, !gpio_get(LED_PIN));

        write_data(0x40);
        write_data(0x80);

        // Delay for 500 milliseconds
        sleep_ms(500);
    }

    return 0;
}