#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void POKEY_init(int sample_rate, int chips);
void POKEY_POKE(int addr, uint8_t value);
uint8_t POKEY_process(void);

#ifdef __cplusplus
}
#endif
