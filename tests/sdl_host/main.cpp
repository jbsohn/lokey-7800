#include <SDL2/SDL.h>
#include "../../src/sound/pokey.h"
#include "demo.h"

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512

extern void demo_scale_frame(int ms_elapsed);

void audio_callback(void *, Uint8 *stream, const int len) {
    for (int i = 0; i < len; ++i) {
        stream[i] = POKEY_process() ^ 0x80;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec desired_spec;
    SDL_zero(desired_spec);
    desired_spec.freq = SAMPLE_RATE;
    desired_spec.format = AUDIO_U8;
    desired_spec.channels = 1;
    desired_spec.samples = BUFFER_SIZE;
    desired_spec.callback = audio_callback;

    SDL_AudioSpec obtained_spec;
    if (SDL_OpenAudio(&desired_spec, &obtained_spec) < 0) {
        fprintf(stderr, "SDL_OpenAudio failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    POKEY_init(SAMPLE_RATE, 1);
    for (int i = 0; i < 16; i++) {
        POKEY_POKE(i, 0);
    }
    POKEY_POKE(0x00, 0xF0);  // AUDF1 = low frequency (tone)
    POKEY_POKE(0x01, 0xA8);  // AUDC1 = pure tone
    POKEY_POKE(0x0F, 0x03);  // SKCTL = enable audio clock

    SDL_PauseAudio(0);

    while (1) {
        demo_scale_frame(10); // Call your melody function here
        SDL_Delay(10);
    }
}
