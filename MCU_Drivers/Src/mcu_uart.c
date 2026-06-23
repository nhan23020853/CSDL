#include "mcu_uart.h"
#include "stm32f4xx.h"
#include "comm.h" // Nhúng Comm để đẩy byte thẳng vào State Machine

void MCU_UART_Init(void) {
    RCC->APB2ENR |= (1U << 5);
    RCC->AHB1ENR |= (1U << 2);

    GPIOC->MODER &= ~((3U << (6*2)) | (3U << (7*2)));
    GPIOC->MODER |=  ((2U << (6*2)) | (2U << (7*2)));
    GPIOC->AFR[0] &= ~((0xFU << (6*4)) | (0xFU << (7*4)));
    GPIOC->AFR[0] |=  ((8U << (6*4)) | (8U << (7*4)));


    USART6->CR1 |= (1U<<13);
}

void USART2_IRQHandler(void) {
    if (USART2->SR & (1U << 5)) {
        Comm_ReceiveByte(USART2->DR);
    }
}

void MCU_UART_Send(uint8_t *data, uint16_t len) {
    for(uint16_t i=0; i<len; i++) {
        while(!(USART2->SR & (1U<<7)));
        USART2->DR = data[i];
    }
    while(!(USART2->SR & (1U<<6)));
}
