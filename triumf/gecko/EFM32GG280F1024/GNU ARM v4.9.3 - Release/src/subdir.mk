################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/InitDevice.c \
../src/clock.c \
../src/clockApp_stk.c \
../src/fatfs.c \
../src/low_power_tick_management.c \
../src/main.c \
../src/microsd.c \
../src/print.c 

OBJS += \
./src/InitDevice.o \
./src/clock.o \
./src/clockApp_stk.o \
./src/fatfs.o \
./src/low_power_tick_management.o \
./src/main.o \
./src/microsd.o \
./src/print.o 

C_DEPS += \
./src/InitDevice.d \
./src/clock.d \
./src/clockApp_stk.d \
./src/fatfs.d \
./src/low_power_tick_management.d \
./src/main.d \
./src/microsd.d \
./src/print.d 


# Each subdirectory must supply rules for building sources it contributes
src/InitDevice.o: ../src/InitDevice.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/InitDevice.d" -MT"src/InitDevice.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/clock.o: ../src/clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/clock.d" -MT"src/clock.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/clockApp_stk.o: ../src/clockApp_stk.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/clockApp_stk.d" -MT"src/clockApp_stk.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fatfs.o: ../src/fatfs.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/fatfs.d" -MT"src/fatfs.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/low_power_tick_management.o: ../src/low_power_tick_management.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/low_power_tick_management.d" -MT"src/low_power_tick_management.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/microsd.o: ../src/microsd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/microsd.d" -MT"src/microsd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/print.o: ../src/print.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DNDEBUG=1' '-DEFM32GG280F1024=1' -I"C:\Users\sdamk\Workspace\ExAlta2-Dev\triumf\gecko\EFM32GG280F1024\inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Source/portable/GCC/ARM_CM3" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//util/third_party/freertos/Demo/Common/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32_Gxxx_STK/examples/freertos_blink" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/inc" -I"C:/Users/sdamk/Workspace/ExAlta2-Dev/triumf/gecko/EFM32GG280F1024/FatFS/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/print.d" -MT"src/print.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


