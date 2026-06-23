################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCU_Drivers/Src/mcu_encoder.c \
../MCU_Drivers/Src/mcu_gpio.c \
../MCU_Drivers/Src/mcu_pwm.c \
../MCU_Drivers/Src/mcu_uart.c 

OBJS += \
./MCU_Drivers/Src/mcu_encoder.o \
./MCU_Drivers/Src/mcu_gpio.o \
./MCU_Drivers/Src/mcu_pwm.o \
./MCU_Drivers/Src/mcu_uart.o 

C_DEPS += \
./MCU_Drivers/Src/mcu_encoder.d \
./MCU_Drivers/Src/mcu_gpio.d \
./MCU_Drivers/Src/mcu_pwm.d \
./MCU_Drivers/Src/mcu_uart.d 


# Each subdirectory must supply rules for building sources it contributes
MCU_Drivers/Src/%.o MCU_Drivers/Src/%.su MCU_Drivers/Src/%.cyclo: ../MCU_Drivers/Src/%.c MCU_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/documentss/cosodoluong/HAL/Inc" -I"D:/documentss/cosodoluong/Application/Inc" -I"D:/documentss/cosodoluong/MCU_Drivers/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCU_Drivers-2f-Src

clean-MCU_Drivers-2f-Src:
	-$(RM) ./MCU_Drivers/Src/mcu_encoder.cyclo ./MCU_Drivers/Src/mcu_encoder.d ./MCU_Drivers/Src/mcu_encoder.o ./MCU_Drivers/Src/mcu_encoder.su ./MCU_Drivers/Src/mcu_gpio.cyclo ./MCU_Drivers/Src/mcu_gpio.d ./MCU_Drivers/Src/mcu_gpio.o ./MCU_Drivers/Src/mcu_gpio.su ./MCU_Drivers/Src/mcu_pwm.cyclo ./MCU_Drivers/Src/mcu_pwm.d ./MCU_Drivers/Src/mcu_pwm.o ./MCU_Drivers/Src/mcu_pwm.su ./MCU_Drivers/Src/mcu_uart.cyclo ./MCU_Drivers/Src/mcu_uart.d ./MCU_Drivers/Src/mcu_uart.o ./MCU_Drivers/Src/mcu_uart.su

.PHONY: clean-MCU_Drivers-2f-Src

