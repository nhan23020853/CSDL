#ifndef PLATFORM_MOTOR_H
#define PLATFORM_MOTOR_H
#include <stdint.h>

void Platform_Motor_Init(void);
void Platform_Motor_SetDuty(uint8_t id, float duty_percent);

#endif
