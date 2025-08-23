#include <array>
#include <cstdio>
#include "pico/stdlib.h"

#include <pico/bootrom.h>

constexpr std::array<uint8_t, 8> dataPins = {2, 3, 4, 5, 6, 7, 8, 9};  // D0-D7
constexpr std::array<uint8_t, 4> addrPins = {10, 11, 12, 13};          // A0-A3
constexpr uint8_t csPin = 14;                                          // /CS
constexpr uint8_t wrPin = 15;                                          // /WR

void setPins(const std::array<uint8_t, 8>& pins, const uint8_t value) {
    for (int i = 0; i < 8; ++i) {
        gpio_put(pins[i], (value >> i) & 1);
    }
}
void setPins(const std::array<uint8_t, 4>& pins, const uint8_t value) {
    for (int i = 0; i < 4; ++i) {
        printf("setPins(%i) = %i\n", pins[i], value);
        gpio_put(pins[i], value >> i & 1);
    }
}

void pokeyWrite(const uint8_t reg, const uint8_t value) {
    printf("pokeyWrite reg: %i value: %i\n", reg, value);

    setPins(addrPins, reg & 0x0F);  // Only 4 bits for $4000-$400F
    setPins(dataPins, value);

    gpio_put(csPin, false);  // /CS LOW (active)
    gpio_put(wrPin, false);  // /WR LOW (active)

    sleep_us(2);  // Short pulse, adjust as needed

    gpio_put(wrPin, true);  // /WR HIGH (inactive)
    gpio_put(csPin, true);  // /CS HIGH (inactive)
}

void setupPins() {
    for (const auto pin : dataPins) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }
    for (const auto pin : addrPins) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }
    gpio_init(csPin);
    gpio_set_dir(csPin, GPIO_OUT);
    gpio_init(wrPin);
    gpio_set_dir(wrPin, GPIO_OUT);
    gpio_put(csPin, true);  // Idle state HIGH
    gpio_put(wrPin, true);  // Idle state HIGH
}

int main() {
    stdio_init_all();
    setupPins();

    for (int i = 0; i < 10; ++i) {
        // Play a 440 Hz A4 tone (AUDF1=144, AUDC1=0xA2)
        pokeyWrite(0x00, 144);   // AUDF1
        pokeyWrite(0x01, 0xA2);  // AUDC1

        sleep_ms(2000);  // Hold tone for 2 seconds

        // Silence channel 1 (volume = 0)
        pokeyWrite(0x01, 0x00);  // AUDC1 = 0 (mute)
    }
    reset_usb_boot(0, 0);
}
