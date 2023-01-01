################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/NKRO_Keypad/NKRO_KEYPAD.c \
../ECUAL/NKRO_Keypad/NKRO_KEYPAD_CFG.c 

OBJS += \
./ECUAL/NKRO_Keypad/NKRO_KEYPAD.o \
./ECUAL/NKRO_Keypad/NKRO_KEYPAD_CFG.o 

C_DEPS += \
./ECUAL/NKRO_Keypad/NKRO_KEYPAD.d \
./ECUAL/NKRO_Keypad/NKRO_KEYPAD_CFG.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/NKRO_Keypad/%.o ECUAL/NKRO_Keypad/%.su: ../ECUAL/NKRO_Keypad/%.c ECUAL/NKRO_Keypad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive/OneDrive/Design Projects/Macro Pad/Macropad-V2/Macropad V2 Code/ECUAL/NKRO_Keypad" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ECUAL-2f-NKRO_Keypad

clean-ECUAL-2f-NKRO_Keypad:
	-$(RM) ./ECUAL/NKRO_Keypad/NKRO_KEYPAD.d ./ECUAL/NKRO_Keypad/NKRO_KEYPAD.o ./ECUAL/NKRO_Keypad/NKRO_KEYPAD.su ./ECUAL/NKRO_Keypad/NKRO_KEYPAD_CFG.d ./ECUAL/NKRO_Keypad/NKRO_KEYPAD_CFG.o ./ECUAL/NKRO_Keypad/NKRO_KEYPAD_CFG.su

.PHONY: clean-ECUAL-2f-NKRO_Keypad

