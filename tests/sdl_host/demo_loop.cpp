#include "../../src/sound/pokey.h"
#include <stdint.h>

// Tone values (frequency dividers)
static const uint8_t tone_pattern[] = {
    0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x48,
    0x50, 0x48, 0x40, 0x38, 0x30, 0x28, 0x20, 0x18
};

static int tone_index = 0;
static int frame_counter = 0;

// Called every frame (~60Hz)
void demo_loop_frame() {
    if (++frame_counter >= 10) {
        frame_counter = 0;

        uint8_t tone = tone_pattern[tone_index];
        tone_index = (tone_index + 1) % (sizeof(tone_pattern));

        // Write to POKEY frequency registers (AUDF)
        POKEY_POKE(0x00, tone); // Channel 1 freq
        POKEY_POKE(0x01, tone); // Channel 2 freq

        // Set volume (AUDC) - simple square wave
        POKEY_POKE(0x04, 0xA0); // Volume + poly
        POKEY_POKE(0x05, 0xA0); // Volume + poly
    }
}