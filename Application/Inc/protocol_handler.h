#ifndef PROTOCOL_HANDLER_H
#define PROTOCOL_HANDLER_H
#include <stdint.h>

void Protocol_Init(void);
void Protocol_SendTelemetry(float rpm, float kp, float ki, float kd);
void Protocol_SendWarning(uint8_t code);

#endif
