################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FatFS/src/diskio.c \
../FatFS/src/ff.c 

OBJS += \
./FatFS/src/diskio.o \
./FatFS/src/ff.o 

C_DEPS += \
./FatFS/src/diskio.d \
./FatFS/src/ff.d 


# Each subdirectory must supply rules for building sources it contributes
FatFS/src/diskio.o: ../FatFS/src/diskio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"FatFS/src/diskio.d" -MT"FatFS/src/diskio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FatFS/src/ff.o: ../FatFS/src/ff.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"FatFS/src/ff.d" -MT"FatFS/src/ff.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


