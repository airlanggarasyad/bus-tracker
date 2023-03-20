################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GNSS/Target/custom_gnss.c \
../GNSS/Target/gnss_lib_config.c \
../GNSS/Target/stm32_bus_ex.c 

OBJS += \
./GNSS/Target/custom_gnss.o \
./GNSS/Target/gnss_lib_config.o \
./GNSS/Target/stm32_bus_ex.o 

C_DEPS += \
./GNSS/Target/custom_gnss.d \
./GNSS/Target/gnss_lib_config.d \
./GNSS/Target/stm32_bus_ex.d 


# Each subdirectory must supply rules for building sources it contributes
GNSS/Target/%.o GNSS/Target/%.su: ../GNSS/Target/%.c GNSS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../GNSS/App -I../GNSS/Target -I../Drivers/BSP/STM32WLxx_Nucleo -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GNSS-2f-Target

clean-GNSS-2f-Target:
	-$(RM) ./GNSS/Target/custom_gnss.d ./GNSS/Target/custom_gnss.o ./GNSS/Target/custom_gnss.su ./GNSS/Target/gnss_lib_config.d ./GNSS/Target/gnss_lib_config.o ./GNSS/Target/gnss_lib_config.su ./GNSS/Target/stm32_bus_ex.d ./GNSS/Target/stm32_bus_ex.o ./GNSS/Target/stm32_bus_ex.su

.PHONY: clean-GNSS-2f-Target

