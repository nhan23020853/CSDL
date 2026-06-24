#include "platform_encoder.h"
#include "mcu_encoder.h"
#include "stm32f4xx_hal.h"

// Khai báo extern để file này "nhìn thấy" các Timer của hệ thống
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

#define PULSES_PER_REV 1496.0f
#define SAMPLING_TIME 0.01f

// Mảng lưu giá trị cũ cho 2 cụm (bạn chỉ dùng 2 cụm)
static uint16_t prev_counts[2] = {0};

void Platform_Encoder_Init(void) {
    MCU_Encoder_Init();
    prev_counts[0] = MCU_Encoder_GetCount(0);
    prev_counts[1] = MCU_Encoder_GetCount(1);
}

float Platform_Encoder_GetRPM(uint8_t id) {
    if (id > 1) return 0.0f; // Chỉ quản lý 2 cụm (0 và 1)

    uint16_t curr_count = MCU_Encoder_GetCount(id);

    // Tính delta an toàn với số nguyên có dấu (để xử lý tràn số - overflow)
    int16_t delta = (int16_t)(curr_count - prev_counts[id]);
    prev_counts[id] = curr_count;

    // RPM = (delta / pulses_per_rev) * (60s / sampling_time)
    return ((float)delta / PULSES_PER_REV) * (60.0f / SAMPLING_TIME);
}
