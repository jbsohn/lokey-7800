#include <algorithm>
#include <vector>
#include "ymfm_2151.hpp"

Ymfm2151::Ymfm2151(const int sampleRate, const int bufferSize)
    : sampleRate(sampleRate), bufferSize(bufferSize), chip(chip_interface) {
    buffer.resize(bufferSize);
}

void Ymfm2151::reset() {
    chip.reset();
    std::ranges::fill(buffer, 0);
}

std::vector<int16_t> Ymfm2151::renderAudio() {
    // Render audio using the YMFM OPM chip
    // The YMFM chip.generate function fills a buffer with stereo samples
    std::vector<ymfm::ymfm_output<2>> tempBuf(bufferSize);
    chip.generate(tempBuf.data(), bufferSize);
    for (int i = 0; i < bufferSize; ++i) {
        const int32_t left = tempBuf[i].data[0];
        const int32_t right = tempBuf[i].data[1];
        int32_t mixed = (left + right) / 2;
        mixed *= 12;  // TODO: increasing volume 12x to start
        mixed = std::clamp(mixed, static_cast<int32_t>(-32768), static_cast<int32_t>(32767));
        buffer[i] = static_cast<int16_t>(mixed);
    }
    return buffer;
}

void Ymfm2151::selectRegister(const uint8_t reg) {
    selectedRegister = reg;
}

void Ymfm2151::writeData(const uint8_t value) {
    chip.write(0, selectedRegister);
    chip.write(1, value);
}

uint8_t Ymfm2151::readStatus() {
    return chip.read(0);
}
