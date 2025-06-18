#include <stdint.h>
#include "../../src/sound/pokey.h"

static const struct {
    uint8_t audf1;
    uint8_t audc1;
    uint16_t duration_ms;
} melody[] = {
    { 0x30, 0xA0, 300 }, // C
    { 0x28, 0xA0, 300 }, // D
    { 0x20, 0xA0, 300 }, // E
    { 0x18, 0xA0, 300 }, // F
    { 0x10, 0xA0, 600 }, // G
    { 0x00, 0x00, 200 }, // Rest
    { 0x18, 0xA0, 300 }, // F
    { 0x10, 0xA0, 300 }, // G
    { 0x30, 0xA0, 800 }, // C (repeat)
};

static int note_idx = 0;
static int note_timer = 0;

void demo_melody_frame(int ms_elapsed) {
    if (note_timer <= 0 && note_idx < sizeof(melody)/sizeof(melody[0])) {
        const auto *n = &melody[note_idx++];
        POKEY_POKE(0x00, n->audf1); // Frequency
        POKEY_POKE(0x04, n->audc1); // Volume/polynomial
        note_timer = n->duration_ms;
    } else if (note_timer > 0) {
        note_timer -= ms_elapsed;
    }
}