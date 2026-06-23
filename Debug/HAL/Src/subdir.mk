################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Src/comm.c \
../HAL/Src/platform_button.c \
../HAL/Src/platform_encoder.c \
../HAL/Src/platform_motor.c 

OBJS += \
./HAL/Src/comm.o \
./HAL/Src/platform_button.o \
./HAL/Src/platform_encoder.o \
./HAL/Src/platform_motor.o 

C_DEPS += \
./HAL/Src/comm.d \
./HAL/Src/platform_button.d \
./HAL/Src/platform_encoder.d \
./HAL/Src/platform_motor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Src/%.o HAL/Src/%.su HAL/Src/%.cyclo: ../HAL/Src/%.c HAL/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/documentss/cosodoluong/HAL/Inc" -I"D:/documentss/cosodoluong/Application/Inc" -I"D:/documentss/cosodoluong/MCU_Drivers/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-Src

clean-HAL-2f-Src:
	-$(RM) ./HAL/Src/comm.cyclo ./HAL/Src/comm.d ./HAL/Src/comm.o ./HAL/Src/comm.su ./HAL/Src/platform_button.cyclo ./HAL/Src/platform_button.d ./HAL/Src/platform_button.o ./HAL/Src/platform_button.su ./HAL/Src/platform_encoder.cyclo ./HAL/Src/platform_encoder.d ./HAL/Src/platform_encoder.o ./HAL/Src/platform_encoder.su ./HAL/Src/platform_motor.cyclo ./HAL/Src/platform_motor.d ./HAL/Src/platform_motor.o ./HAL/Src/platform_motor.su

.PHONY: clean-HAL-2f-Src

