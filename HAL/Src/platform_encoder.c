#include "platform_encoder.h"
#include "mcu_encoder.h"

#define PULSES_PER_REV 1496.0f
#define SAMPLING_TIME 0.01f

// Lưu trữ giá trị cũ cho từng bánh
static uint16_t prev_counts[4] = {0};

void Platform_Encoder_Init(void) {
    MCU_Encoder_Init(); // Cần đảm bảo hàm này khởi tạo 4 Timer Encoder
    for(int i = 0; i < 4; i++) {
        prev_counts[i] = MCU_Encoder_GetCount(i);
    }
}

float Platform_Encoder_GetRPM(uint8_t id) {
    if (id > 3) return 0.0f;

    uint16_t curr_count = MCU_Encoder_GetCount(id);
    int16_t delta = (int16_t)(curr_count - prev_counts[id]);
    prev_counts[id] = curr_count;

    return ((float)delta / PULSES_PER_REV) * (60.0f / SAMPLING_TIME);
}
