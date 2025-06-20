/*
 * pokey_globals.c - Stubbed global variables required by pokey.c
 *
 * This file defines a minimal set of global symbols that pokey.c depends on,
 * normally provided by the full Atari800 emulator. These are included here to
 * satisfy linker requirements in the LOKEY project and may be adjusted as
 * integration progresses.
 */
#include "atari.h"

int CPU_IRQ = 0;               // Stub for interrupt handling flag used by pokey.c
int PBI_IRQ = 0;               // Stub for PBI-related interrupt flag (unused in LOKEY)
int ESC_enable_sio_patch = 0;  // Stub for SIO patch toggle, not used in standalone builds
