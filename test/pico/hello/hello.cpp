#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

[[noreturn]] int main() {
    constexpr uint LED = PICO_DEFAULT_LED_PIN;  // 25 on Pico
    constexpr uint TX_PIN = 0;
    constexpr uint RX_PIN = 1;

    stdio_init_all();
    uart_init(uart0, 115200);
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    while (true) {
        uart_puts(uart0, "Hello from Pico!\r\n");
        gpio_xor_mask(1u << LED);
        sleep_ms(250);
    }
}
