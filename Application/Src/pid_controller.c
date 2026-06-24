#include "pid_controller.h"

void PID_Init(PID_Config_t *pid, float kp, float ki, float kd, float dt) {
    pid->Kp = kp; pid->Ki = ki;
    pid->Kd = kd; pid->dt = dt;
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
    pid->windup_status = 0;
}

float PID_Compute(PID_Config_t *pid, float setpoint, float measured) {
    float error = setpoint - measured;
    pid->integral += error * pid->dt;
    pid->windup_status = 0;

    if(pid->integral > 100.0f) { pid->integral = 100.0f; pid->windup_status = 1; }
    else if(pid->integral < -100.0f) {
    	pid->integral = -100.0f;
    	pid->windup_status = 1; }

    float d = (error - pid->prev_error) / pid->dt;
    float out = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * d);
    pid->prev_error = error;
    return out;
}
