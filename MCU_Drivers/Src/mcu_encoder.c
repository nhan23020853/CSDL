#include "mcu_encoder.h"
#include "stm32f4xx_hal.h"  // <--- BẮT BUỘC PHẢI CÓ DÒNG NÀY (để có TIM_HandleTypeDef)
#include <stdint.h>         // <--- BẮT BUỘC PHẢI CÓ DÒNG NÀY (để có uint16_t, uint8_t)

// Khai báo extern các Timer bạn dùng
extern TIM_HandleTypeDef htim3; // Encoder Trái
extern TIM_HandleTypeDef htim4; // Encoder Phải (PB6/PB7)

void MCU_Encoder_Init(void) {
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

uint16_t MCU_Encoder_GetCount(uint8_t id) {
    switch(id) {
        case 0: return __HAL_TIM_GET_COUNTER(&htim3);
        case 1: return __HAL_TIM_GET_COUNTER(&htim4);
        default: return 0;
    }
}
