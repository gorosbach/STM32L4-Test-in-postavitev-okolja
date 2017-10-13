################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HTS221_Hum.c \
../Src/LPS22HM_Press.c \
../Src/main.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_it.c \
../Src/syscall.c \
../Src/system_stm32l4xx.c 

OBJS += \
./Src/HTS221_Hum.o \
./Src/LPS22HM_Press.o \
./Src/main.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_it.o \
./Src/syscall.o \
./Src/system_stm32l4xx.o 

C_DEPS += \
./Src/HTS221_Hum.d \
./Src/LPS22HM_Press.d \
./Src/main.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_it.d \
./Src/syscall.d \
./Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32L475xx -I"/home/gorazd/Documents/CUBE_Projects/TEST_UART/Inc" -I"/home/gorazd/Documents/CUBE_Projects/TEST_UART/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/home/gorazd/Documents/CUBE_Projects/TEST_UART/Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/home/gorazd/Documents/CUBE_Projects/TEST_UART/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/home/gorazd/Documents/CUBE_Projects/TEST_UART/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


