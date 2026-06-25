#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "mcu_encoder.h"
#include "platform_motor.h"
#include "control_app.h"
#include "stm32f4xx_hal.h"
#include "platform_encoder.h"
#include "mcu_gpio.h"
#include "mcu_uart.h"
#include <stdio.h>
#include <string.h>

void SystemClock_Config(void);

float Kp = 0.4f, Kd = 0.0f;

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART6_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

  MCU_UART_Init();
  MCU_Encoder_Init();
  Platform_Motor_Init();
  ControlApp_Init();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
  HAL_TIM_Base_Start_IT(&htim9);

  static uint32_t last_uart_time = 0;
  static uint32_t last_btn_time = 0;

  while (1)
  {
      // --- LOGIC NÚT BẤM (Nút 1 chỉnh Kp, Nút 2 chỉnh Kd) ---
      if (HAL_GetTick() - last_btn_time > 150) {
          last_btn_time = HAL_GetTick();
          uint8_t pid_changed = 0;

          if (MCU_GPIO_ReadButton(1) == 0) { // Giữ nút 1: Chỉnh Kp
              if (MCU_GPIO_ReadButton(3) == 0) { Kp += 0.1f; pid_changed = 1; }
              if (MCU_GPIO_ReadButton(4) == 0) { Kp -= 0.1f; pid_changed = 1; }
          }
          else if (MCU_GPIO_ReadButton(2) == 0) { // Giữ nút 2: Chỉnh Kd trở lại
              if (MCU_GPIO_ReadButton(3) == 0) { Kd += 0.1f; pid_changed = 1; }
              if (MCU_GPIO_ReadButton(4) == 0) { Kd -= 0.1f; pid_changed = 1; }
          }

          if (Kp < 0) Kp = 0;
          if (Kd < 0) Kd = 0;

          if (pid_changed) {
              ControlApp_UpdatePID(Kp, Kd);
          }
      }

      if (HAL_GetTick() - last_uart_time > 500) {
          last_uart_time = HAL_GetTick();
          char uart_buf[128];

          sprintf(uart_buf, "Spd_L: %d | Spd_R: %d | Kp: %.2f | Kd: %.2f\r\n",
                  (int)ControlApp_GetCurrentRPM(0),
                  (int)ControlApp_GetCurrentRPM(1),
                  Kp, Kd);

          MCU_UART_Send((uint8_t*)uart_buf, strlen(uart_buf));
      }
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13)
    {
        static uint32_t last_interrupt_time = 0;
        uint32_t current_time = HAL_GetTick();

        if ((current_time - last_interrupt_time) > 250) {
            ControlApp_TogglePIDMode();
            last_interrupt_time = current_time;
        }
    }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM9)
  {
    ControlApp_ControlLoop_ISR();
  }
}

void Error_Handler(void) { while (1) { } }
