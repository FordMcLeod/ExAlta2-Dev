################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
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
all: EFM32GG280F1024.axf

# Tool invocations
EFM32GG280F1024.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "EFM32GG280F1024.ld" -Xlinker --gc-sections -Xlinker -Map="EFM32GG280F1024.map" --specs=nano.specs -o EFM32GG280F1024.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_system.o" "./src/InitDevice.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: EFM32GG280F1024.hex'
	arm-none-eabi-objcopy -O ihex "EFM32GG280F1024.axf" "EFM32GG280F1024.hex"
	@echo ' '

	@echo 'Building bin file: EFM32GG280F1024.bin'
	arm-none-eabi-objcopy -O binary "EFM32GG280F1024.axf" "EFM32GG280F1024.bin"
	@echo ' '

	@echo 'Building s37 file: EFM32GG280F1024.s37'
	arm-none-eabi-objcopy -O srec "EFM32GG280F1024.axf" "EFM32GG280F1024.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "EFM32GG280F1024.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) EFM32GG280F1024.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
