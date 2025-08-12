#pragma once

#include <vector>
#include "ymfm_opm.h"

class Ym2151Interface final : public ymfm::ymfm_interface {
};

class Ymfm2151 final {
public:
    Ymfm2151(int sampleRate, int bufferSize);
    void reset();

    void selectRegister(uint8_t reg);
    void writeData(uint8_t value);
    uint8_t readStatus();

    std::vector<int16_t> renderAudio();

private:
    int sampleRate;
    int bufferSize;
    std::vector<int16_t> buffer;
    Ym2151Interface chip_interface{};
    ymfm::ym2151 chip;
    uint8_t selectedRegister = 0;
};