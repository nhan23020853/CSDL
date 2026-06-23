#ifndef CONTROL_APP_H
#define CONTROL_APP_H
#include "pid_controller.h"

typedef struct {
    PID_Config_t pid;
    float current_rpm;
    float target_rpm;
} Wheel_t;

void ControlApp_Init(void);
void ControlApp_ControlLoop_ISR(void);
void ControlApp_SetWheelParameters(uint8_t wheel_idx, float target, float kp, float ki, float kd);

#endif
