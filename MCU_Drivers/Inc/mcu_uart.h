#ifndef MCU_UART_H
#define MCU_UART_H
#include <stdint.h>

void MCU_UART_Init(void);
void MCU_UART_Send(uint8_t *data, uint16_t len);

#endif
