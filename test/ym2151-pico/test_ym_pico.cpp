#include <cmath>

#include "pico/stdlib.h"
#include "audio/pico_pwm_audio_sink.hpp"
#include "nuked_opm_ym.hpp"
#include "audio/pico_gpio_audio_sink.hpp"
#include "pico/bootrom.h"

int main2() {
    stdio_init_all();

    constexpr uint32_t SAMPLE_RATE = 44100;
    constexpr int PWM_PIN = 0; // <- set to your wired pin

    PicoPwmAudioSink sink(PWM_PIN, 13u, SAMPLE_RATE, 512, 4);
    sink.start();

    const int framesPerBlock = static_cast<int>(sink.getBufferSize());
    NukedOpmYM ym(SAMPLE_RATE, framesPerBlock);
    ym.reset();

    // 🎹 WRITE A BASIC PATCH TO ACTIVATE SOUND
    // Set up a basic FM tone on Channel 0

    // Operator 1 settings
    ym.writeReg(0x30, 0x71); // DT1=7, MUL=1
    ym.writeReg(0x38, 0x0F); // TL=15
    ym.writeReg(0x40, 0x26); // RS=2, AR=6
    ym.writeReg(0x48, 0x04); // AM=0, D1R=4
    ym.writeReg(0x50, 0x00); // D2R=0
    ym.writeReg(0x58, 0x33); // D1L=3, RR=3
    ym.writeReg(0x60, 0x0C); // FB/ALG = feedback 0, algorithm 4
    ym.writeReg(0xA0, 0x69); // FNUM low
    ym.writeReg(0xA4, 0x22); // Block/FNUM high
    ym.writeReg(0x28, 0xF0); // Key ON: all 4 operators on channel 0

    // Loop to render audio
    while (true) {
        const auto samples = ym.renderAudio();
        sink.writeAudio(samples);
    }
    // KEY OFF
    reset_usb_boot(0, 0);
    return 0;
}

constexpr int sampleRate = 44100;
constexpr float frequency = 440.0f;
constexpr float amplitude = 0.25f;
constexpr int durationSeconds = 2;

int main() {
    PicoPwmAudioSink sink(0, 13u, sampleRate, 512, 4);

    constexpr int bufferSize = 512;
    int16_t buffer[bufferSize];

    constexpr float twoPiF = 2.0f * 3.14159265359f * frequency;

    constexpr int totalSamples = sampleRate * durationSeconds;
    int sampleIndex = 0;

    while (sampleIndex < totalSamples) {
        for (int i = 0; i < bufferSize && sampleIndex < totalSamples; ++i, ++sampleIndex) {
            const float t = static_cast<float>(sampleIndex) / sampleRate;
            const float value = std::sin(twoPiF * t);
            buffer[i] = static_cast<int16_t>(value * amplitude * 32767.0f);
        }

        sink.writeAudio({buffer, bufferSize});
    }

    return 0;
}