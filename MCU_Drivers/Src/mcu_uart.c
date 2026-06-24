#include "mcu_uart.h"
#include "stm32f4xx.h"
#include "comm.h"

void MCU_UART_Init(void) {
    // Clock cho USART6 (APB2) và Port C (AHB1)
    RCC->APB2ENR |= (1U << 5);
    RCC->AHB1ENR |= (1U << 2);

    // Cấu hình PC6 (TX), PC7 (RX) thành Alternate Function 8 (USART6)
    GPIOC->MODER &= ~((3U << 12) | (3U << 14));
    GPIOC->MODER |=  ((2U << 12) | (2U << 14));
    GPIOC->AFR[0] &= ~((0xFU << 24) | (0xFU << 28));
    GPIOC->AFR[0] |=  ((8U << 24) | (8U << 28));

    // Bật USART6 và ngắt nhận (RXNEIE)
    USART6->CR1 |= (1U << 13) | (1U << 5);
    NVIC_EnableIRQ(USART6_IRQn);
}

void USART6_IRQHandler(void) {
    // Khi có dữ liệu đến
    if (USART6->SR & (1U << 5)) {
        Comm_ReceiveByte(USART6->DR);
    }
}

void MCU_UART_Send(uint8_t *data, uint16_t len) {
    for(uint16_t i=0; i<len; i++) {
        // Đợi cờ TXE (Transmit data register empty)
        while(!(USART6->SR & (1U<<7)));
        USART6->DR = data[i];
    }
    // Đợi cờ TC (Transmission complete)
    while(!(USART6->SR & (1U<<6)));
}
