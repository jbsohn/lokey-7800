#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "sound/pokey.h"

const uint AUDIO_PIN = 15;

void setup_pwm() {
    gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);
    pwm_set_wrap(slice_num, 255);
    pwm_set_enabled(slice_num, true);
}

int main() {
    stdio_init_all();
    setup_pwm();

    POKEY_init(44100, 1);
    POKEY_POKE(1, 10);   // AUDF1
    POKEY_POKE(0, 0xA8); // AUDC1 (pure tone)

    uint slice_num = pwm_gpio_to_slice_num(AUDIO_PIN);
    while (true) {
        uint8_t sample = POKEY_process();
        pwm_set_chan_level(slice_num, PWM_CHAN_A, sample);
        sleep_us(22); // ~44.1kHz
    }
}
