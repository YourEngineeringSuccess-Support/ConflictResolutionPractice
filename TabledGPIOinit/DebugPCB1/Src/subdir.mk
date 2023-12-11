################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO_Sys.c 

OBJS += \
./Src/GPIO_Sys.o 

C_DEPS += \
./Src/GPIO_Sys.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DPCBVariant1 -DSTM32 -DSTM32F429ZITx -DSTM32F4 -c -I../Inc -I../Inc/STM32F4Headers -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/GPIO_Sys.cyclo ./Src/GPIO_Sys.d ./Src/GPIO_Sys.o ./Src/GPIO_Sys.su

.PHONY: clean-Src

