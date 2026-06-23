// MCU_Drivers/Inc/mcu_gpio.h
#ifndef MCU_GPIO_H
#define MCU_GPIO_H

#include <stdint.h>

void MCU_GPIO_Init(void);
// Bổ sung dòng này để file platform_motor.c nhận diện được
void MCU_GPIO_Write(uint8_t pin_id, uint8_t state);
uint8_t MCU_GPIO_ReadButton(uint8_t btn_id);

#endif
