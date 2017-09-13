################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0/platform/emdrv/sleep/src/sleep.c 

OBJS += \
./Drivers/sleep.o 

C_DEPS += \
./Drivers/sleep.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/sleep.o: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0/platform/emdrv/sleep/src/sleep.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/sleep.d" -MT"Drivers/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


