################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GNSS/App/app_gnss.c 

OBJS += \
./GNSS/App/app_gnss.o 

C_DEPS += \
./GNSS/App/app_gnss.d 


# Each subdirectory must supply rules for building sources it contributes
GNSS/App/%.o GNSS/App/%.su: ../GNSS/App/%.c GNSS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../GNSS/App -I../GNSS/Target -I../Drivers/BSP/STM32WLxx_Nucleo -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GNSS-2f-App

clean-GNSS-2f-App:
	-$(RM) ./GNSS/App/app_gnss.d ./GNSS/App/app_gnss.o ./GNSS/App/app_gnss.su

.PHONY: clean-GNSS-2f-App

