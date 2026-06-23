#include "mcu_encoder.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

void MCU_Encoder_Init(void) {
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // Encoder Trái
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL); // Encoder Phải
}

uint16_t MCU_Encoder_GetCount(uint8_t id) {
    switch(id) {
        case 0: return __HAL_TIM_GET_COUNTER(&htim3);
        case 1: return __HAL_TIM_GET_COUNTER(&htim1);
        default: return 0;
    }
}
