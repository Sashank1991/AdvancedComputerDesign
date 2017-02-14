################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Adafruit-GFX-Library-master/glcdfont.c 

OBJS += \
./src/Adafruit-GFX-Library-master/glcdfont.o 

C_DEPS += \
./src/Adafruit-GFX-Library-master/glcdfont.d 


# Each subdirectory must supply rules for building sources it contributes
src/Adafruit-GFX-Library-master/%.o: ../src/Adafruit-GFX-Library-master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\sasha\Documents\LPCXpresso_7.9.0_455\workspace\CMSIS_CORE_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


