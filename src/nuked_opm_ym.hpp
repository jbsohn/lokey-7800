#pragma once

#include <cstdint>
#include <vector>
#include <span>

#include "opm.h"

class NukedOpmYM final {
public:
    NukedOpmYM(int sampleRate, int bufferSize);
    void reset();
    void writeAddress(uint8_t reg);
    void writeData(uint8_t value);
    void writePort(uint8_t port, uint8_t value);
    void writeReg(uint8_t reg, uint8_t value);
    std::vector<int16_t> renderAudio();

private:
    int sampleRate;
    int bufferSize;
    std::vector<int16_t> buffer;
    opm_t chip{};

    void process(int32_t* output_buffer, size_t frames, int num_channels = 2);
};