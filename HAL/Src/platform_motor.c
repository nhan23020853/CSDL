#include "platform_motor.h"
#include "mcu_gpio.h"
#include "mcu_pwm.h"

#define MAX_PWM_PERIOD 1000.0f

void Platform_Motor_Init(void) {
    MCU_GPIO_Init(); // Đảm bảo hàm này cấu hình đủ 8 chân GPIO cho 4 bánh
    MCU_PWM_Init();  // Đảm bảo cấu hình đủ 4 kênh PWM
}

void Platform_Motor_SetDuty(uint8_t id, float duty) {
    if (id > 3) return; // Bảo vệ truy cập ngoài mảng

    if (duty > 100.0f) duty = 100.0f;
    if (duty < -100.0f) duty = -100.0f;

    // Giả sử mỗi bánh dùng 2 chân GPIO:
    // Bánh 0: Chân 0, 1 | Bánh 1: Chân 2, 3 | Bánh 2: Chân 4, 5 | Bánh 3: Chân 6, 7
    uint8_t pin_in1 = id * 2;
    uint8_t pin_in2 = id * 2 + 1;

    if (duty >= 0) {
        MCU_GPIO_Write(pin_in1, 1);
        MCU_GPIO_Write(pin_in2, 0);
    } else {
        MCU_GPIO_Write(pin_in1, 0);
        MCU_GPIO_Write(pin_in2, 1);
        duty = -duty;
    }

    // Giả sử MCU_PWM_SetDutyCycle_Channel nhận (id, value)
    uint16_t pwm_val = (uint16_t)((duty / 100.0f) * MAX_PWM_PERIOD);
    MCU_PWM_SetDutyCycle_Channel(id, pwm_val);
}
