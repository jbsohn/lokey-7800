#include <array>
#include "NukedOpmYM.hpp"

NukedOpmYM::NukedOpmYM(int sampleRate, int bufferSize) : sampleRate(sampleRate), bufferSize(bufferSize) {
    buffer.reserve(bufferSize);
}

void NukedOpmYM::reset() {
    OPM_Reset(&chip);
    OPM_SetIC(&chip, 0);
    OPM_SetIC(&chip, 1);
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

std::span<const int16_t> NukedOpmYM::renderAudio() {
    // Ensure buffer sized in case bufferSize changed dynamically
    if (buffer.size() < static_cast<size_t>(bufferSize)) {
        buffer.resize(static_cast<size_t>(bufferSize));
    }

    for (int i = 0; i < bufferSize; ++i) {
        std::array<int32_t, 2> out = {0, 0};
        uint8_t sh1 = 0, sh2 = 0, so = 0;
        OPM_Clock(&chip, out.data(), &sh1, &sh2, &so);

        int32_t mono = (out[0] + out[1]) >> 1;
        mono >>= 8;

        if (mono > 32767) {
            mono = 32767;
        }
        if (mono < -32768) {
            mono = -32768;
        }

        buffer[static_cast<size_t>(i)] = static_cast<int16_t>(mono);
    }

    return {buffer.data(), static_cast<size_t>(bufferSize)};
}
