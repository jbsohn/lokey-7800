#include "pico/stdlib.h"
#include <array>

constexpr std::array<uint8_t, 8> dataPins = {2, 3, 4, 5, 6, 7, 8, 9};  // D0-D7
constexpr std::array<uint8_t, 4> addrPins = {10, 11, 12, 13};          // A0-A3
constexpr uint8_t csPin = 14;                                          // /CS
constexpr uint8_t wrPin = 15;                                          // /WR

[[noreturn]]
int main() {
    stdio_init_all();

    for (const auto pin : dataPins) {
        gpio_init(pin), gpio_set_dir(pin, GPIO_OUT);
    }
    for (const auto pin : addrPins) {
        gpio_init(pin), gpio_set_dir(pin, GPIO_OUT);
    }
    gpio_init(csPin);
    gpio_set_dir(csPin, GPIO_OUT);
    gpio_put(csPin, false);
    gpio_init(wrPin);
    gpio_set_dir(wrPin, GPIO_OUT);
    gpio_put(wrPin, true);

    while (true) {
        for (int i = 0; i < 4; i++) {
            constexpr uint8_t address = 0x4;
            gpio_put(addrPins[i], address >> i & 1);
        }
        for (int i = 0; i < 8; i++) {
            constexpr uint8_t data = 0xAB;
            gpio_put(dataPins[i], data >> i & 1);
        }

        gpio_put(wrPin, false);
        sleep_us(2);
        gpio_put(wrPin, true);

        sleep_ms(1);
    }
}
