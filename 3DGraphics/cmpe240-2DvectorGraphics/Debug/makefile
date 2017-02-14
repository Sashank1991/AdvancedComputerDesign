################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Adafruit-GFX-Library-master/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cmpe240-2DvectorGraphics.axf

# Tool invocations
cmpe240-2DvectorGraphics.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\sasha\Documents\LPCXpresso_7.9.0_455\workspace\CMSIS_CORE_LPC17xx\Debug" -Xlinker -Map="cmpe240-2DvectorGraphics.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "cmpe240-2DvectorGraphics_Debug.ld" -o "cmpe240-2DvectorGraphics.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) cmpe240-2DvectorGraphics.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "cmpe240-2DvectorGraphics.axf"; # arm-none-eabi-objcopy -v -O binary "cmpe240-2DvectorGraphics.axf" "cmpe240-2DvectorGraphics.bin" ; # checksum -p LPC1769 -d "cmpe240-2DvectorGraphics.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
