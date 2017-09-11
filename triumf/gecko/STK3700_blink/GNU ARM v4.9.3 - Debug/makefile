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
-include BSP/subdir.mk
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
all: STK3700_blink.axf

# Tool invocations
STK3700_blink.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "STK3700_blink.ld" -Xlinker --gc-sections -Xlinker -Map="STK3700_blink.map" --specs=nano.specs -o STK3700_blink.axf "./BSP/bsp_bcc.o" "./BSP/bsp_stk.o" "./BSP/bsp_stk_leds.o" "./BSP/bsp_trace.o" "./CMSIS/EFM32GG/startup_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_ebi.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_system.o" "./emlib/em_usart.o" "./src/blink.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: STK3700_blink.hex'
	arm-none-eabi-objcopy -O ihex "STK3700_blink.axf" "STK3700_blink.hex"
	@echo ' '

	@echo 'Building bin file: STK3700_blink.bin'
	arm-none-eabi-objcopy -O binary "STK3700_blink.axf" "STK3700_blink.bin"
	@echo ' '

	@echo 'Building s37 file: STK3700_blink.s37'
	arm-none-eabi-objcopy -O srec "STK3700_blink.axf" "STK3700_blink.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "STK3700_blink.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) STK3700_blink.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
