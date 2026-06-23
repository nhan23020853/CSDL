#include "mcu_gpio.h"
#include "stm32f4xx.h"

void MCU_GPIO_Init(void) {
    // Clock: A=0, B=1, C=2
    RCC->AHB1ENR |= (1U << 0) | (1U << 1) | (1U << 2);

    // --- PA4, PA5 (Motor) ---
    GPIOA->MODER &= ~((3U << 8) | (3U << 10));
    GPIOA->MODER |=  ((1U << 8) | (1U << 10));

    // --- PC13, PB0, PB1, PB2 (Nút bấm) ---
    // PC13
    GPIOC->MODER &= ~(3U << (13 * 2));
    // PB0, PB1, PB2
    GPIOB->MODER &= ~((3U << 0) | (3U << 2) | (3U << 4));
    GPIOB->PUPDR |= ((1U << 0) | (1U << 2) | (1U << 4)); // Pull-up
}

uint8_t MCU_GPIO_ReadButton(uint8_t btn_id) {
    if (btn_id == 0) return (GPIOC->IDR & (1U << 13)) ? 1 : 0; // PC13
    if (btn_id == 1) return (GPIOB->IDR & (1U << 0))  ? 1 : 0; // PB0
    if (btn_id == 2) return (GPIOB->IDR & (1U << 1))  ? 1 : 0; // PB1
    if (btn_id == 3) return (GPIOB->IDR & (1U << 2))  ? 1 : 0; // PB2
    return 1;
}

void MCU_GPIO_Write(uint8_t pin_id, uint8_t state) {
    if (pin_id == 0) { // Điều khiển IN1 (PA4)
        if (state) GPIOA->BSRR = (1U << 4);      // Set High
        else       GPIOA->BSRR = (1U << (4+16)); // Reset Low
    }
    else if (pin_id == 1) { // Điều khiển IN2 (PA5)
        if (state) GPIOA->BSRR = (1U << 5);      // Set High
        else       GPIOA->BSRR = (1U << (5+16)); // Reset Low
    }
}
