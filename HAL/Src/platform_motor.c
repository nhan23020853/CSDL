#include "platform_motor.h"
#include "mcu_gpio.h"
#include "mcu_pwm.h"
#include "stm32f4xx.h"
#include "mcu_uart.h"
#include <string.h>

#define MAX_PWM_PERIOD 1000.0f

void Platform_Motor_Init(void) {
    MCU_GPIO_Init();
    MCU_PWM_Init();
    GPIOA->BSRR = (1U << 10);
}

void Platform_Motor_SetDuty(uint8_t id, float duty) {
    if (id > 1) return;

    if (id == 0) { // Cụm Trái: PA4(AIN1), PC0(AIN2)
        if (duty >= 0) {
            GPIOA->BSRR = (1U << 4);        // PA4 High
            GPIOC->BSRR = (1U << (0+16));   // PC0 Low
        } else {
            GPIOA->BSRR = (1U << (4+16));   // PA4 Low
            GPIOC->BSRR = (1U << 0);        // PC0 High
        }
    } else { // Cụm Phải: PB10, PB15
        if (duty >= 0) {
            GPIOB->BSRR = (1U << 10);
            GPIOB->BSRR = (1U << (15+16));
        } else {
            GPIOB->BSRR = (1U << (10+16));
            GPIOB->BSRR = (1U << 15);
        }
    }
    // Set PWM
    float abs_duty = (duty < 0) ? -duty : duty;
    uint16_t pwm_val = (uint16_t)((abs_duty / 100.0f) * 1000.0f);
    MCU_PWM_SetDutyCycle_Channel(id, pwm_val);
}
