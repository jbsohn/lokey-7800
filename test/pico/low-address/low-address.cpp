#include <stdio.h>
#include <array>
#include "pico/stdlib.h"

constexpr uint TX_PIN = 0;
constexpr uint RX_PIN = 1;

constexpr uint8_t A0_PIN = 10;
constexpr uint8_t A1_PIN = 11;
constexpr uint8_t A2_PIN = 12;
constexpr uint8_t A3_PIN = 13;

void init_addr_pins() {
    gpio_init(A0_PIN);
    gpio_init(A1_PIN);
    gpio_init(A2_PIN);
    gpio_init(A3_PIN);

    gpio_set_dir(A0_PIN, GPIO_IN);
    gpio_set_dir(A1_PIN, GPIO_IN);
    gpio_set_dir(A2_PIN, GPIO_IN);
    gpio_set_dir(A3_PIN, GPIO_IN);
}

uint8_t read_addr_nibble() {
    return gpio_get(A3_PIN) << 3 | gpio_get(A2_PIN) << 2 | gpio_get(A1_PIN) << 1 | gpio_get(A0_PIN) << 0;
}

[[noreturn]] int main() {
    uart_init(uart0, 115200);
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    init_addr_pins();

    uart_puts(uart0, "7800 address probe starting...\r\n");

    while (true) {
        std::array<char, 80> line;
        const uint8_t addr = read_addr_nibble();
        snprintf(line.data(), sizeof(line), "A[3:0] = %X\r\n", addr);
        uart_puts(uart0, line.data());
    }
}
