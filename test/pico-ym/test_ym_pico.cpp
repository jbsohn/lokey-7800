#include "pico/stdlib.h"
#include "audio/pico_pwm_audio_sink.hpp"
#include "audio/null_audio_sink.hpp"
#include "audio/pico_gpio_audio_sink.hpp"
#include "ymfm_2151.hpp"
#include "pico/bootrom.h"

void write_reg(Ymfm2151& ym, const uint8_t reg, const uint8_t value) {
    ym.selectRegister(reg);
    ym.writeData(value);
}

void test(Ymfm2151& ym) {
    write_reg(ym, 0x18, 0x00); // LFO off
    write_reg(ym, 0x20, 0xC0); // ch0: pan L+R, FB=0, ALG=0 (simple sine)
    // Operator TL: carrier (op3) = 0x00 (loudest), others = 0x7F (silent)
    write_reg(ym, 0x60, 0x7F); // op0 TL
    write_reg(ym, 0x68, 0x7F); // op1 TL
    write_reg(ym, 0x70, 0x7F); // op2 TL
    write_reg(ym, 0x78, 0x00); // op3 TL (carrier, loudest)
    // Operator MULT: all = 1 except carrier (op3) = 2
    write_reg(ym, 0x40, 0x01); // op0
    write_reg(ym, 0x48, 0x01); // op1
    write_reg(ym, 0x50, 0x01); // op2
    write_reg(ym, 0x58, 0x02); // op3 (carrier)
    // Envelope: fast attack, no decay, max sustain, no release
    for (int op = 0; op < 4; ++op) {
        write_reg(ym, 0x80 + op * 8, 0x1F); // AR
    }
    for (int op = 0; op < 4; ++op) {
        write_reg(ym, 0xA0 + op * 8, 0x00); // D1R
    }
    for (int op = 0; op < 4; ++op) {
        write_reg(ym, 0xA8 + op * 8, 0x0F); // D1L
    }
    for (int op = 0; op < 4; ++op) {
        write_reg(ym, 0xC0 + op * 8, 0x00); // D2R
    }
    for (int op = 0; op < 4; ++op) {
        write_reg(ym, 0xE0 + op * 8, 0x00); // RR
    }
    write_reg(ym, 0x28, 0x00); // FNUM LSB
    write_reg(ym, 0x30, 0x50); // BLOCK=5, FNUM MSB=0 (high pitch)
    write_reg(ym, 0x08, 0xF0); // Key on all ops, ch0
}

int main() {
    constexpr int sampleRate = 22050;
    constexpr int bufferSize = 256;

    stdio_init_all();

    printf("starting Ymfm2151...\n");
    Ymfm2151 ym(sampleRate, bufferSize);
    ym.reset();

    printf("starting audio sink...\n");
    PicoPwmAudioSink sink(0, 8u, sampleRate, bufferSize, 4);
    sink.start();

    printf("starting test...\n");
    test(ym);

    printf("YMFM YM2151 SDLAudioSink test running. SampleRate=%d, BufferSize=%d\n", sampleRate, bufferSize);
    for (int i = 0; i < 1024; ++i) {
        std::vector<int16_t> buf = ym.renderAudio();
        sink.writeAudio(buf);
    }

    sink.stop();
    ym.reset();
    printf("Test completed successfully.\n");

    reset_usb_boot(0, 0);
    return 0;
}
