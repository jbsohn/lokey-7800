#include "../../src/sound/pokey.h"

static int melody_timer = 0;
static int current_note = 0;

// Frequencies tuned for AUDF values with 64kHz base clock approximation.
// These values are ballpark — actual tuning would be tighter in a real tracker.
static const uint8_t notes[] = {
    121, // C4
    108, // D4
    96,  // E4
    91,  // F4
    80,  // G4
    71,  // A4
    63,  // B4
    59   // C5
};

static const int note_duration_ms = 400;

void demo_scale_frame(int ms_elapsed) {
    melody_timer += ms_elapsed;

    if (melody_timer >= note_duration_ms) {
        melody_timer -= note_duration_ms;

        // Quiet channel
        POKEY_POKE(0x01, 0x00);

        // Set freq + enable clean tone
        POKEY_POKE(0x00, notes[current_note]);
        POKEY_POKE(0x01, 0xA8); // AUDC1: vol=8, pure tone, use 64kHz

        current_note = (current_note + 1) % (sizeof(notes) / sizeof(notes[0]));
    }

    // Set stable control values once per frame
    POKEY_POKE(0x08, 0x00); // AUDCTL: all channels 64kHz
    POKEY_POKE(0x0F, 0x00); // SKCTL: no special modes
}
