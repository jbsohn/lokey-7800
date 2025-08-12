#include <SDL.h>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory>
#include <vector>
#include "ymfm_2151.hpp"

std::unique_ptr<Ymfm2151> gYM;
static std::atomic<bool> gReady{false};
static int gBufferSize = 0;

void write_reg(uint8_t reg, uint8_t value) {
    gYM->selectRegister(reg);
    gYM->writeData(value);
}

void key_on_test_patch() {
    write_reg(0x18, 0x00); // LFO off
    write_reg(0x20, 0xC7); // ch0: pan L+R, FB=0, ALG=7
    for (int op = 0; op < 4; ++op) write_reg(0x60 + op * 8, 0x10); // TL
    for (int op = 0; op < 4; ++op) write_reg(0x40 + op * 8, 0x01); // MULT=1
    for (int op = 0; op < 4; ++op) write_reg(0x80 + op * 8, 0x1F); // AR (fast attack)
    for (int op = 0; op < 4; ++op) write_reg(0xA0 + op * 8, 0x00); // D1R (no decay)
    for (int op = 0; op < 4; ++op) write_reg(0xA8 + op * 8, 0x0F); // D1L (max sustain)
    for (int op = 0; op < 4; ++op) write_reg(0xC0 + op * 8, 0x00); // D2R (no 2nd decay)
    for (int op = 0; op < 4; ++op) write_reg(0xE0 + op * 8, 0x00); // RR (no release)
    write_reg(0x28, 0x00); // FNUM LSB
    write_reg(0x30, 0x40); // BLOCK=4, FNUM MSB=0
    write_reg(0x08, 0xF0); // Key on all ops, ch0
}

void render(int16_t* out, int samples) {
    // Get audio from Ymfm2151 and copy to out
    std::vector<int16_t> buf = gYM->renderAudio();
    int n = std::min(samples, (int)buf.size());
    for (int i = 0; i < n; ++i) {
        out[i] = buf[i];
    }
    // Zero any remaining samples if needed
    for (int i = n; i < samples; ++i) {
        out[i] = 0;
    }
}

void SDLCALL audioCallback(void*, Uint8* stream, int lenBytes) {
    printf("Audio callback: lenBytes=%d\n", lenBytes);
    if (!gReady.load(std::memory_order_relaxed)) {
        std::memset(stream, 0, lenBytes);
        return;
    }
    int16_t* out = reinterpret_cast<int16_t*>(stream);
    int frames = lenBytes / sizeof(int16_t);
    render(out, frames);
}

int main(int argc, char** argv) {
    const int sampleRate = 44100;
    gBufferSize = 512;

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetHint(SDL_HINT_AUDIO_RESAMPLING_MODE, "trivial");

    SDL_AudioSpec want{};
    want.freq = sampleRate;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = gBufferSize;
    want.callback = audioCallback;

    SDL_AudioSpec have{};
    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
    if (!dev) {
        std::fprintf(stderr, "SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    gYM = std::make_unique<Ymfm2151>(sampleRate, gBufferSize);
    gYM->reset();
    key_on_test_patch();

    gReady.store(true, std::memory_order_relaxed);
    SDL_PauseAudioDevice(dev, 0);

    std::printf("YMFM YM2151 SDL test running. SampleRate=%d, BufferSize=%d\n", have.freq, gBufferSize);
    std::printf("Press Enter to quit.\n");
    (void)getchar();

    SDL_PauseAudioDevice(dev, 1);
    gReady.store(false, std::memory_order_relaxed);
    gYM.reset();
    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    return 0;
}