#include <array>
#include <cstdio>
#include "pico/stdlib.h"

constexpr std::array<uint8_t, 8> dataPins = {2, 3, 4, 5, 6, 7, 8, 9};  // D0-D7
constexpr std::array<uint8_t, 4> addrPins = {10, 11, 12, 13};          // A0-A3
constexpr uint8_t csPin = 14;                                          // /CS
constexpr uint8_t wrPin = 15;                                          // /WR

constexpr int32_t PRINT_INTERVAL = 10000;

[[noreturn]]
int main() {
    stdio_init_all();

    for (const auto pin : dataPins) {
        gpio_init(pin), gpio_set_dir(pin, GPIO_IN), gpio_pull_down(pin);
    }
    for (const auto pin : addrPins) {
        gpio_init(pin), gpio_set_dir(pin, GPIO_IN), gpio_pull_down(pin);
    }
    gpio_init(csPin);
    gpio_set_dir(csPin, GPIO_IN), gpio_pull_up(csPin);
    gpio_init(wrPin);
    gpio_set_dir(wrPin, GPIO_IN), gpio_pull_up(wrPin);

    bool prevWr = true;
    uint32_t count = 0;
    uint32_t lastCount = 0;
    absolute_time_t lastPrint = get_absolute_time();

    while (true) {
        const bool wr = gpio_get(wrPin);
        if (prevWr && !wr) {
            uint8_t address = 0, data = 0;
            for (int i = 0; i < 4; i++) {
                address |= gpio_get(addrPins[i]) << i;
            }
            for (int i = 0; i < 8; i++) {
                data |= gpio_get(dataPins[i]) << i;
            }

            count++;
            if (count % PRINT_INTERVAL == 0) {
                const absolute_time_t now = get_absolute_time();
                const int64_t us = absolute_time_diff_us(lastPrint, now);

                const uint32_t writesThisPeriod = count - lastCount;
                const float writesPerSec = static_cast<float>(writesThisPeriod) * 1e6f / static_cast<float>(us);

                printf("Total writes: %lu, Writes per sec: %.0f\n", count, writesPerSec);

                lastCount = count;
                lastPrint = now;
            }
        }
        prevWr = wr;
        sleep_us(1);
    }
}
