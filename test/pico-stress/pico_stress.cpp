#include "pico/stdlib.h"
#include <array>

constexpr std::array<uint8_t, 8> dataPins = {2, 3, 4, 5, 6, 7, 8, 9};  // D0-D7
constexpr std::array<uint8_t, 4> addrPins = {10, 11, 12, 13};           // A0-A3
constexpr uint8_t csPin = 14;                                           // /CS
constexpr uint8_t wrPin = 15;                                           // /WR
constexpr uint8_t ledPin = 25;                                          // Onboard LED

int main() {
    // Init all pins as input
    for (auto pin : dataPins) gpio_init(pin), gpio_set_dir(pin, GPIO_IN);
    for (auto pin : addrPins) gpio_init(pin), gpio_set_dir(pin, GPIO_IN);
    gpio_init(csPin); gpio_set_dir(csPin, GPIO_IN);
    gpio_init(wrPin); gpio_set_dir(wrPin, GPIO_IN);
    gpio_init(ledPin); gpio_set_dir(ledPin, GPIO_OUT);

    volatile uint32_t junk = 0;
    while (true) {
        // Fastest possible pin reads
        uint8_t data = 0;
        for (int i = 0; i < 8; ++i) {
            data |= (gpio_get(dataPins[i]) << i);
        }

        uint8_t addr = 0;
        for (int i = 0; i < 4; ++i) {
            addr |= (gpio_get(addrPins[i]) << i);
        }

        uint8_t cs = gpio_get(csPin);
        uint8_t wr = gpio_get(wrPin);

        // Do some "work" to keep the core busy
        junk ^= (data << 8) | (addr << 4) | (cs << 1) | wr;
        junk += (data ^ addr ^ cs ^ wr);

        // Optionally toggle LED for more draw
        gpio_put(ledPin, (junk & 0x1));
    }
    return 0;
}
