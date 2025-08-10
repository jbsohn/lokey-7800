#include "audio/sdl_audio_sink.hpp"
#include "nuked_opm_ym.hpp"

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;

    std::cout << "Starting YM2151 test..." << std::endl;

    // Initialize audio sink
    SDLAudioSink sink(44100, 512);
    sink.start();

    // Initialize YM2151
    NukedOpmYM ym(44100, 512);
    ym.reset();

    // Example: simple tone on channel 0 using operator 0
    ym.writeReg(0x20, 0x01); // CH0 Operator 0: detune=0, multiple=1
    ym.writeReg(0x40, 0x3F); // CH0 Operator 0: total level = 63 (lower volume)
    ym.writeReg(0x60, 0x0F); // CH0 Operator 0: attack rate
    ym.writeReg(0x80, 0x77); // CH0 Operator 0: decay rate
    ym.writeReg(0xA0, 0x00); // CH0: Frequency LSB
    ym.writeReg(0xA8, 0x1F); // CH0: Frequency MSB (key-on)
    sink.writeAudio(ym.renderAudio());

    // Enable only operator 0 on channel 0
    ym.writeReg(0xB0, 0x32); // CH0: connect=2, feedback=1
    ym.writeReg(0xB4, 0xC0); // CH0: key on
    const auto samples = ym.renderAudio();
    sink.writeAudio(ym.renderAudio());

    // Output mixing — enable all channels
    ym.writeReg(0x1B, 0xC0); // L+R output enable (Global)
    sink.writeAudio(ym.renderAudio());

    // Feed audio for 2 seconds
    for (int i = 0; i < 48000 * 2; ++i) {
        // 2 seconds @ 48kHz
        auto samples = ym.renderAudio();
        sink.writeAudio(samples);
    }

    std::cout << "Finished playback." << std::endl;
    return 0;
}
