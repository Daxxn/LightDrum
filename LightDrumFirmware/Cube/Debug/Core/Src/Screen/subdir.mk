################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Screen/Button.cpp \
../Core/Src/Screen/Component.cpp \
../Core/Src/Screen/Control.cpp \
../Core/Src/Screen/Page.cpp 

OBJS += \
./Core/Src/Screen/Button.o \
./Core/Src/Screen/Component.o \
./Core/Src/Screen/Control.o \
./Core/Src/Screen/Page.o 

CPP_DEPS += \
./Core/Src/Screen/Button.d \
./Core/Src/Screen/Component.d \
./Core/Src/Screen/Control.d \
./Core/Src/Screen/Page.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Screen/%.o Core/Src/Screen/%.su Core/Src/Screen/%.cyclo: ../Core/Src/Screen/%.cpp Core/Src/Screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Vx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Screen

clean-Core-2f-Src-2f-Screen:
	-$(RM) ./Core/Src/Screen/Button.cyclo ./Core/Src/Screen/Button.d ./Core/Src/Screen/Button.o ./Core/Src/Screen/Button.su ./Core/Src/Screen/Component.cyclo ./Core/Src/Screen/Component.d ./Core/Src/Screen/Component.o ./Core/Src/Screen/Component.su ./Core/Src/Screen/Control.cyclo ./Core/Src/Screen/Control.d ./Core/Src/Screen/Control.o ./Core/Src/Screen/Control.su ./Core/Src/Screen/Page.cyclo ./Core/Src/Screen/Page.d ./Core/Src/Screen/Page.o ./Core/Src/Screen/Page.su

.PHONY: clean-Core-2f-Src-2f-Screen

