#ifndef PLATFORM_ENCODER_H
#define PLATFORM_ENCODER_H
#include <stdint.h>

void Platform_Encoder_Init(void);
float Platform_Encoder_GetRPM(uint8_t id);

#endif
