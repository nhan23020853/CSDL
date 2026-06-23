#include "platform_motor.h"
#include "mcu_gpio.h"
#include "mcu_pwm.h"

#define MAX_PWM_PERIOD 1000.0f

void Platform_Motor_Init(void) {
    MCU_GPIO_Init();
    MCU_PWM_Init();
}

void Platform_Motor_SetDuty(uint8_t id, float duty) {
    if (id > 3) return; // Bảo vệ truy cập ngoài mảng

    if (duty > 100.0f) duty = 100.0f;
    if (duty < -100.0f) duty = -100.0f;

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

    uint16_t pwm_val = (uint16_t)((duty / 100.0f) * MAX_PWM_PERIOD);
    MCU_PWM_SetDutyCycle_Channel(id, pwm_val);
}
