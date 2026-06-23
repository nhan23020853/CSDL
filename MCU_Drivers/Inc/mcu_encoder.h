#ifndef MCU_ENCODER_H
#define MCU_ENCODER_H
#include <stdint.h>

void MCU_Encoder_Init(void);
uint16_t MCU_Encoder_GetCount(uint8_t id);
#endif
