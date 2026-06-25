#include "mcu_gpio.h"
#include "stm32f4xx.h"

void MCU_GPIO_Init(void) {
    // 1. Bật Clock cho Port A, B, C
    RCC->AHB1ENR |= (1U << 0) | (1U << 1) | (1U << 2);

    // 2. Cấu hình Driver Motor làm OUTPUT
    // AIN1: PA4, AIN2: PC0, STBY: PA10, BIN1: PB10, BIN2: PB15

    // Clear PA4, PA10, PC0
    GPIOA->MODER &= ~((3U << 8) | (3U << 20));
    GPIOC->MODER &= ~(3U << 0);
    // Set Output (01) cho PA4, PA10, PC0
    GPIOA->MODER |=  ((1U << 8) | (1U << 20));
    GPIOC->MODER |=  (1U << 0);

    // Clear PB10, PB15
    GPIOB->MODER &= ~((3U << 20) | (3U << 30));
    // Set Output (01) cho PB10, PB15
    GPIOB->MODER |=  ((1U << 20) | (1U << 30));

    // Bật sẵn STBY (PA10)
    GPIOA->BSRR = GPIO_PIN_10;

    // 3. Cấu hình Nút bấm INPUT PULL-UP (PB0, PB1, PB2, PB4, PC13)
    // Nút 4 đã chuyển từ PB3 sang PB4
    GPIOB->MODER &= ~((3U << 0) | (3U << 2) | (3U << 4) | (3U << 8));
    GPIOB->PUPDR &= ~((3U << 0) | (3U << 2) | (3U << 4) | (3U << 8));
    GPIOB->PUPDR |=  ((1U << 0) | (1U << 2) | (1U << 4) | (1U << 8));

    GPIOC->MODER &= ~(3U << 26);
    GPIOC->PUPDR |=  (1U << 26);
}

uint8_t MCU_GPIO_ReadButton(uint8_t btn_id) {
    if (btn_id == 1) return (GPIOB->IDR & (1U << 0)) ? 1 : 0; // PB0
    if (btn_id == 2) return (GPIOB->IDR & (1U << 1)) ? 1 : 0; // PB1
    if (btn_id == 3) return (GPIOB->IDR & (1U << 2)) ? 1 : 0; // PB2
    if (btn_id == 4) return (GPIOB->IDR & (1U << 4)) ? 1 : 0; // PB4
    if (btn_id == 0) return (GPIOC->IDR & (1U << 13)) ? 1 : 0; // PC13
    return 1;
}
