#include "pokey.h"
#include <string.h>

#define SAMPLE_RATE 44100
#define SYSTEM_Clock 1789790

static uint8_t pokey_registers[16];

void POKEY_init(int sample_rate, int chips) {
    memset(pokey_registers, 0, sizeof(pokey_registers));
    pokey_registers[1] = 0x10;  // Default tone divider for audible output
}

void POKEY_POKE(int addr, uint8_t value) {
    if (addr < 16) {
        pokey_registers[addr] = value;
    }
}

uint8_t POKEY_process(void) {
    static int tone_phase = 0;
    static int tone_counter = 0;
    static int note_index = 0;
    static int note_duration = 0;

    static const int scale[] = {
        262, // C4
        294, // D4
        330, // E4
        349, // F4
        392, // G4
        440, // A4
        494, // B4
        523, // C5
        494, // B4
        440, // A4
        392, // G4
        349, // F4
        330, // E4
        294, // D4
        262  // C4
    };
    const int num_notes = sizeof(scale) / sizeof(scale[0]);

    int freq = scale[note_index];

    tone_counter++;
    if (tone_counter >= SAMPLE_RATE / freq / 2) {
        tone_counter = 0;
        tone_phase = !tone_phase;
    }

    note_duration++;
    if (note_duration > SAMPLE_RATE / 4) { // Change note every ~0.25s
        note_duration = 0;
        note_index = (note_index + 1) % num_notes;
    }

    return tone_phase ? 0xFF : 0x00;
}
