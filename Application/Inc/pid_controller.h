#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include <stdint.h>

typedef struct {
    float Kp, Ki, Kd, dt;
    float integral, prev_error;
    uint8_t windup_status;
} PID_Config_t;

void PID_Init(PID_Config_t *pid, float kp, float ki, float kd, float dt);
float PID_Compute(PID_Config_t *pid, float setpoint, float measured);

#endif
