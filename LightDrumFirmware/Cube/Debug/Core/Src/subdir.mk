################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

CPP_SRCS += \
../Core/Src/MainWrapper.cpp \
../Core/Src/Nextion.cpp \
../Core/Src/PCA9634.cpp \
../Core/Src/ScreenControl.cpp \
../Core/Src/ShiftRegs.cpp \
../Core/Src/StripControl.cpp \
../Core/Src/StripCurrent.cpp \
../Core/Src/Utils.cpp 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 

OBJS += \
./Core/Src/MainWrapper.o \
./Core/Src/Nextion.o \
./Core/Src/PCA9634.o \
./Core/Src/ScreenControl.o \
./Core/Src/ShiftRegs.o \
./Core/Src/StripControl.o \
./Core/Src/StripCurrent.o \
./Core/Src/Utils.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

CPP_DEPS += \
./Core/Src/MainWrapper.d \
./Core/Src/Nextion.d \
./Core/Src/PCA9634.d \
./Core/Src/ScreenControl.d \
./Core/Src/ShiftRegs.d \
./Core/Src/StripControl.d \
./Core/Src/StripCurrent.d \
./Core/Src/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Vx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F412Vx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/MainWrapper.cyclo ./Core/Src/MainWrapper.d ./Core/Src/MainWrapper.o ./Core/Src/MainWrapper.su ./Core/Src/Nextion.cyclo ./Core/Src/Nextion.d ./Core/Src/Nextion.o ./Core/Src/Nextion.su ./Core/Src/PCA9634.cyclo ./Core/Src/PCA9634.d ./Core/Src/PCA9634.o ./Core/Src/PCA9634.su ./Core/Src/ScreenControl.cyclo ./Core/Src/ScreenControl.d ./Core/Src/ScreenControl.o ./Core/Src/ScreenControl.su ./Core/Src/ShiftRegs.cyclo ./Core/Src/ShiftRegs.d ./Core/Src/ShiftRegs.o ./Core/Src/ShiftRegs.su ./Core/Src/StripControl.cyclo ./Core/Src/StripControl.d ./Core/Src/StripControl.o ./Core/Src/StripControl.su ./Core/Src/StripCurrent.cyclo ./Core/Src/StripCurrent.d ./Core/Src/StripCurrent.o ./Core/Src/StripCurrent.su ./Core/Src/Utils.cyclo ./Core/Src/Utils.d ./Core/Src/Utils.o ./Core/Src/Utils.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

