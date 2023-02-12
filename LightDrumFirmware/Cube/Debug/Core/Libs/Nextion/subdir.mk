################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Libs/Nextion/Nextion.cpp 

OBJS += \
./Core/Libs/Nextion/Nextion.o 

CPP_DEPS += \
./Core/Libs/Nextion/Nextion.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Libs/Nextion/%.o Core/Libs/Nextion/%.su: ../Core/Libs/Nextion/%.cpp Core/Libs/Nextion/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Vx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Libs-2f-Nextion

clean-Core-2f-Libs-2f-Nextion:
	-$(RM) ./Core/Libs/Nextion/Nextion.d ./Core/Libs/Nextion/Nextion.o ./Core/Libs/Nextion/Nextion.su

.PHONY: clean-Core-2f-Libs-2f-Nextion

