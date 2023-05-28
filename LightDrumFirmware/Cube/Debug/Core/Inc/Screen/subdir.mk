################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/Screen/NumberBox.cpp \
../Core/Inc/Screen/PageButton.cpp \
../Core/Inc/Screen/ProgressBar.cpp \
../Core/Inc/Screen/Slider.cpp 

OBJS += \
./Core/Inc/Screen/NumberBox.o \
./Core/Inc/Screen/PageButton.o \
./Core/Inc/Screen/ProgressBar.o \
./Core/Inc/Screen/Slider.o 

CPP_DEPS += \
./Core/Inc/Screen/NumberBox.d \
./Core/Inc/Screen/PageButton.d \
./Core/Inc/Screen/ProgressBar.d \
./Core/Inc/Screen/Slider.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Screen/%.o Core/Inc/Screen/%.su Core/Inc/Screen/%.cyclo: ../Core/Inc/Screen/%.cpp Core/Inc/Screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Vx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Screen

clean-Core-2f-Inc-2f-Screen:
	-$(RM) ./Core/Inc/Screen/NumberBox.cyclo ./Core/Inc/Screen/NumberBox.d ./Core/Inc/Screen/NumberBox.o ./Core/Inc/Screen/NumberBox.su ./Core/Inc/Screen/PageButton.cyclo ./Core/Inc/Screen/PageButton.d ./Core/Inc/Screen/PageButton.o ./Core/Inc/Screen/PageButton.su ./Core/Inc/Screen/ProgressBar.cyclo ./Core/Inc/Screen/ProgressBar.d ./Core/Inc/Screen/ProgressBar.o ./Core/Inc/Screen/ProgressBar.su ./Core/Inc/Screen/Slider.cyclo ./Core/Inc/Screen/Slider.d ./Core/Inc/Screen/Slider.o ./Core/Inc/Screen/Slider.su

.PHONY: clean-Core-2f-Inc-2f-Screen

