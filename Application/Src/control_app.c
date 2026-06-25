#include "control_app.h"
#include "platform_motor.h"
#include "platform_encoder.h"
#include "platform_button.h"
#include "protocol_handler.h"
#include "comm.h"
#include "stm32f4xx.h"
#include <string.h>

static Wheel_t wheels[2];
static uint8_t is_pid_mode = 1;

static void OnFrameReceived(FrameType_t *rx) {
    if (rx->ID == 0x20 && rx->len >= 16) {
        uint8_t id = rx->payload[0];
        if (id > 1) return;

        float target, kp, ki, kd;
        memcpy(&target, &rx->payload[1], 4);
        memcpy(&kp, &rx->payload[5], 4);
        memcpy(&ki, &rx->payload[9], 4);
        memcpy(&kd, &rx->payload[13], 4);
        ControlApp_SetWheelParameters(id, target, kp, ki, kd);
    }
}

void ControlApp_Init(void) {
    for(int i = 0; i < 2; i++) {
        // Khởi tạo PID ban đầu, giữ Ki = 2.0f chạy ngầm để bù sai số lệch bánh
        PID_Init(&wheels[i].pid, 0.4f, 2.0f, 0.0f, 0.01f);
        wheels[i].target_rpm = 20.0f; // Tốc độ thấp an toàn
    }
    Platform_Button_Init();
    Platform_Encoder_Init();
    Platform_Motor_Init();
    Comm_RegisterRxCallback(OnFrameReceived);
}

void ControlApp_SetWheelParameters(uint8_t idx, float t, float kp, float ki, float kd) {
    if (idx >= 2) return;
    __disable_irq();
    wheels[idx].target_rpm = t;
    wheels[idx].pid.Kp = kp;
    wheels[idx].pid.Ki = ki;
    wheels[idx].pid.Kd = kd;
    __enable_irq();
}

void ControlApp_ControlLoop_ISR(void) {
    for(int i = 0; i < 2; i++) {
        wheels[i].current_rpm = Platform_Encoder_GetRPM(i);

        float pwm = 0.0f;

        if (is_pid_mode == 1) {
            pwm = PID_Compute(&wheels[i].pid, wheels[i].target_rpm, wheels[i].current_rpm);
        } else {
            pwm = 25.0f; // Chế độ chạy thô không PID
        }

        if (pwm > 100.0f)  pwm = 100.0f;
        if (pwm < -100.0f) pwm = -100.0f;

        Platform_Motor_SetDuty(i, pwm);
    }

    static uint8_t counter = 0;
    if (++counter >= 10) {
        counter = 0;
        Protocol_SendTelemetry(wheels[0].current_rpm, wheels[1].current_rpm,
                               wheels[0].pid.Kp, wheels[0].pid.Kd);
    }
}

void ControlApp_TogglePIDMode(void) {
    __disable_irq();
    if (is_pid_mode == 1) {
        is_pid_mode = 0;
        for(int i = 0; i < 2; i++) {
            wheels[i].pid.integral = 0.0f;
            wheels[i].pid.prev_error = 0.0f;
        }
    } else {
        is_pid_mode = 1;
    }
    __enable_irq();
}

// Hàm quay trở lại chỉ cập nhật Kp và Kd từ nút bấm, giữ nguyên Ki ngầm định
void ControlApp_UpdatePID(float kp, float kd) {
    __disable_irq();
    for(int i = 0; i < 2; i++) {
        wheels[i].pid.Kp = kp;
        wheels[i].pid.Kd = kd;
    }
    __enable_irq();
}

float ControlApp_GetCurrentRPM(uint8_t id) {
    if (id > 1) return 0.0f;
    return wheels[id].current_rpm;
}
