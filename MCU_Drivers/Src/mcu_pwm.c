#include "mcu_pwm.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim2;

void MCU_PWM_Init(void) {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

void MCU_PWM_SetDutyCycle_Channel(uint8_t id, uint16_t val) {
    switch(id) {
        case 0: __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, val); break; // Cụm Trái
        case 1: __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, val); break; // Cụm Phải
        default: break;
    }
}
