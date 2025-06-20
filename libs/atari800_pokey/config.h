// config.h - Stubbed configuration header for Atari800 integration
#ifndef CONFIG_H
#define CONFIG_H

// Fake any expected defines here

#define HAVE_STDINT_H 1

#ifndef LOKEY_ATARI_H
#define LOKEY_ATARI_H

#include <stdint.h>

typedef uint8_t  UBYTE;
typedef uint16_t UWORD;
typedef uint32_t ULONG;
typedef int32_t  SLONG;

#define TRUE  1
#define FALSE 0

// Missing globals
#define ANTIC_XPOS 0
#define ANTIC_LINE_C 1
int ESC_enable_sio_patch = 0;
int PBI_IRQ = 0;
int CPU_IRQ = 0;

// Missing functions
static inline int CASSETTE_IOLineStatus(void) { return 0; }
static inline void CPU_GenerateIRQ(void) {}
static inline void SIO_PutByte(int byte) {}
static inline int  SIO_GetByte(void) { return 0; }
static inline void CASSETTE_ResetPOKEY(void) {}
static inline int  CASSETTE_AddScanLine(void) { return 0; }
static inline int  INPUT_Playingback(void) { return 0; }
static inline int  INPUT_PlaybackInt(void) { return 0; }
static inline int  INPUT_Recording(void) { return 0; }
static inline void INPUT_RecordInt(int dummy) {}
static inline void INPUT_Scanline(void) {}
static inline void SndSave_CloseSoundFile(void) {}
static inline void SndSave_WriteToSoundFile(const unsigned char*, int) {}

// Needed for pokey.c
#define SIO_SEROUT_INTERVAL 0
#define SIO_XMTDONE_INTERVAL 0

// Needed for pokey.c save/load routines
static inline void StateSav_SaveUBYTE(UBYTE* /*data*/, int /*len*/) {}
static inline void StateSav_SaveINT(int* /*data*/, int /*len*/) {}
static inline void StateSav_ReadUBYTE(UBYTE* /*data*/, int /*len*/) {}
static inline void StateSav_ReadINT(int* /*data*/, int /*len*/) {}

// Fix warning: add parameter names to MZPOKEYSND_Init
static inline int MZPOKEYSND_Init(int snd_freq17, int playback_freq, int num_pokeys, int snd_flags, int quality) {
    return 0;
}

#endif // LOKEY_ATARI_H
#endif /* CONFIG_H */
