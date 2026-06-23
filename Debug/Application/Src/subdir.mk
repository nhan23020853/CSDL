################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Src/control_app.c \
../Application/Src/pid_controller.c \
../Application/Src/protocol_handler.c 

OBJS += \
./Application/Src/control_app.o \
./Application/Src/pid_controller.o \
./Application/Src/protocol_handler.o 

C_DEPS += \
./Application/Src/control_app.d \
./Application/Src/pid_controller.d \
./Application/Src/protocol_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Src/%.o Application/Src/%.su Application/Src/%.cyclo: ../Application/Src/%.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/documentss/cosodoluong/HAL/Inc" -I"D:/documentss/cosodoluong/Application/Inc" -I"D:/documentss/cosodoluong/MCU_Drivers/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Src

clean-Application-2f-Src:
	-$(RM) ./Application/Src/control_app.cyclo ./Application/Src/control_app.d ./Application/Src/control_app.o ./Application/Src/control_app.su ./Application/Src/pid_controller.cyclo ./Application/Src/pid_controller.d ./Application/Src/pid_controller.o ./Application/Src/pid_controller.su ./Application/Src/protocol_handler.cyclo ./Application/Src/protocol_handler.d ./Application/Src/protocol_handler.o ./Application/Src/protocol_handler.su

.PHONY: clean-Application-2f-Src

