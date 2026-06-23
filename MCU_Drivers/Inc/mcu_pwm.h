#ifndef MCU_PWM_H
#define MCU_PWM_H
#include <stdint.h>

void MCU_PWM_Init(void);
// Thay đổi từ SetDutyCycle(val) thành SetDutyCycle_Channel(id, val)
void MCU_PWM_SetDutyCycle_Channel(uint8_t id, uint16_t val);

#endif
