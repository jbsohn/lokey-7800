#include <stdio.h>
#include <array>
#include "pico/stdlib.h"

constexpr uint TX_PIN = 0;
constexpr uint RX_PIN = 1;

// A0–A7, LSB → MSB
constexpr std::array<uint8_t, 8> ADDR_PINS = {
    10,  // A0
    11,  // A1
    12,  // A2
    13,  // A3
    14,  // A4
    15,  // A5
    16,  // A6
    17   // A7
};

void init_addr_pins() {
    for (const auto pin : ADDR_PINS) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
    }
}

uint8_t read_addr_low_byte() {
    uint8_t value = 0;
    for (size_t i = 0; i < ADDR_PINS.size(); ++i) {
        value |= gpio_get(ADDR_PINS[i]) << i;
    }
    return value;
}

[[noreturn]] int main() {
    uart_init(uart0, 115200);
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    uart_set_format(uart0, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(uart0, false);

    sleep_ms(200);  // let UART settle

    init_addr_pins();

    uart_puts(uart0, "7800 address probe starting (A0–A7)...\r\n");

    std::array<char, 80> line;
    while (true) {
        const uint8_t addr = read_addr_low_byte();
        snprintf(line.data(), line.size(), "A[7:0] = %02X\r\n", addr);
        uart_puts(uart0, line.data());
        sleep_ms(50);
    }
}
