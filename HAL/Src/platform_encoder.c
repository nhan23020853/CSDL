#include "platform_encoder.h"
#include "mcu_encoder.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

#define PULSES_PER_REV 1496.0f
#define SAMPLING_TIME 0.01f
#define LPF_ALPHA 0.2f

static uint16_t prev_counts[2] = {0};
static float filtered_rpm[2] = {0.0f, 0.0f};

void Platform_Encoder_Init(void) {
    MCU_Encoder_Init();
    prev_counts[0] = MCU_Encoder_GetCount(0);
    prev_counts[1] = MCU_Encoder_GetCount(1);
    filtered_rpm[0] = 0.0f;
    filtered_rpm[1] = 0.0f;
}

float Platform_Encoder_GetRPM(uint8_t id) {
    if (id > 1) return 0.0f;

    uint16_t curr_count = MCU_Encoder_GetCount(id);
    int16_t delta = (int16_t)(curr_count - prev_counts[id]);
    prev_counts[id] = curr_count;

    float raw_rpm = ((float)delta / PULSES_PER_REV) * (60.0f / SAMPLING_TIME);

    filtered_rpm[id] = (LPF_ALPHA * raw_rpm) + ((1.0f - LPF_ALPHA) * filtered_rpm[id]);

    return -filtered_rpm[id];
}
