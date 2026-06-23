#include "mcu_gpio.h"
#include "stm32f4xx.h"

void MCU_GPIO_Init(void) {
    // Clock: B=1, C=2
    RCC->AHB1ENR |= (1U << 1) | (1U << 2);

    // PC13 (Nút bấm 1)
    GPIOC->MODER &= ~(3U << (13 * 2));

    // PB0, PB1, PB2 (Nút bấm 2, 3, 4)
    GPIOB->MODER &= ~((3U << 0) | (3U << 2) | (3U << 4));
    GPIOB->PUPDR |= ((1U << 0) | (1U << 2) | (1U << 4)); // Pull-up
}

uint8_t MCU_GPIO_ReadButton(uint8_t btn_id) {
    if (btn_id == 0) return (GPIOC->IDR & (1U << 13)) ? 1 : 0;
    if (btn_id == 1) return (GPIOB->IDR & (1U << 0))  ? 1 : 0;
    if (btn_id == 2) return (GPIOB->IDR & (1U << 1))  ? 1 : 0;
    if (btn_id == 3) return (GPIOB->IDR & (1U << 2))  ? 1 : 0;
    return 1;
}
