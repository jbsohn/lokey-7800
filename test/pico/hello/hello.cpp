#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

int main() {
    constexpr uint LED = PICO_DEFAULT_LED_PIN; // 25 on Pico

    stdio_init_all();
    gpio_init(LED); gpio_set_dir(LED, GPIO_OUT);
    while (true) {
        gpio_xor_mask(1u << LED);
        sleep_ms(250);
    }
}
