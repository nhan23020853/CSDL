#include "mcu_uart.h"
#include "stm32f4xx.h"
#include "comm.h" // Nhúng Comm để đẩy byte thẳng vào State Machine

void MCU_UART_Init(void) {
    RCC->APB1ENR |= (1U << 17); // USART2 Clock
    RCC->AHB1ENR |= (1U << 0);  // GPIOA Clock

    // Cấu hình PA2(TX), PA3(RX) Alternate Function AF7
    GPIOA->MODER &= ~((3U << (2*2)) | (3U << (3*2)));
    GPIOA->MODER |=  ((2U << (2*2)) | (2U << (3*2)));
    GPIOA->AFR[0] &= ~((0xFU << (2*4)) | (0xFU << (3*4)));
    GPIOA->AFR[0] |=  ((7U << (2*4)) | (7U << (3*4)));

    // Baudrate 115200 (Giả sử APB1 = 16MHz)
    USART2->CR1 = 0;
    USART2->BRR = (8U << 4) | 11U;

    // Bật TX, RX, Ngắt RX, và USART
    USART2->CR1 |= (1U<<2) | (1U<<3) | (1U<<5) | (1U<<13);
    NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_IRQHandler(void) {
    if (USART2->SR & (1U << 5)) { // Kiểm tra cờ RXNE
        Comm_ReceiveByte(USART2->DR); // Ném byte vào State Machine
    }
}

void MCU_UART_Send(uint8_t *data, uint16_t len) {
    for(uint16_t i=0; i<len; i++) {
        while(!(USART2->SR & (1U<<7))); // Chờ TXE
        USART2->DR = data[i];
    }
    while(!(USART2->SR & (1U<<6))); // Chờ TC
}
