#include <algorithm>
#include <cstdio>
#include "nuked_opm_ym.hpp"

#include <cstring>

NukedOpmYM::NukedOpmYM(int sampleRate, int bufferSize) : sampleRate(sampleRate), bufferSize(bufferSize) {
    buffer.resize(bufferSize);
}

void NukedOpmYM::reset() {
    memset(&chip, 0, sizeof(opm_t));
    OPM_Reset(&chip);
}

void NukedOpmYM::writeAddress(const uint8_t reg) {
    OPM_Write(&chip, 0, reg);
}

void NukedOpmYM::writeData(const uint8_t value) {
    OPM_Write(&chip, 1, value);
}

void NukedOpmYM::writePort(const uint8_t port, const uint8_t value) {
    OPM_Write(&chip, port, value);
}

void NukedOpmYM::writeReg(const uint8_t reg, const uint8_t value) {
    OPM_Write(&chip, 0, reg);
    OPM_Write(&chip, 1, value);
}

std::vector<int16_t> NukedOpmYM::renderAudio() {
    for (int16_t& i : buffer) {
        std::array<int32_t, 2> out;
        OPM_Clock(&chip, out.data(), nullptr, nullptr, nullptr);
        int32_t mixed = (out[0] + out[1]) / 2;
        mixed = std::clamp(mixed, static_cast<int32_t>(-32768), static_cast<int32_t>(32767));
        i = static_cast<int16_t>(mixed);
    }
    return buffer;
}

void NukedOpmYM::process(int32_t* output_buffer, const size_t frames, const int num_channels) {
    int32_t outputs[2];
    uint8_t sh1, sh2, so;

    for (size_t i = 0; i < frames; i++) {
        // Clock the OPM chip for 32 cycles (one sample)
        for (int j = 0; j < 32; j++) {
            OPM_Clock(&chip, j == 31 ? outputs : nullptr, &sh1, &sh2, &so);
        }

        // Copy the output to the buffer according to number of channels
        if (num_channels == 1) {
            // Mono output (mix both channels)
            output_buffer[i] = (outputs[0] + outputs[1]) / 2;
        } else {
            // Stereo output (interleaved)
            output_buffer[i * 2] = outputs[0]; // Left channel
            output_buffer[i * 2 + 1] = outputs[1]; // Right channel
        }
    }
}