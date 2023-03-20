################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/teseo_liv3f/teseo_liv3f.c \
../Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_i2c.c \
../Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_queue.c \
../Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_uart.c 

OBJS += \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f.o \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_i2c.o \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_queue.o \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_uart.o 

C_DEPS += \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f.d \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_i2c.d \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_queue.d \
./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/teseo_liv3f/%.o Drivers/BSP/Components/teseo_liv3f/%.su: ../Drivers/BSP/Components/teseo_liv3f/%.c Drivers/BSP/Components/teseo_liv3f/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../GNSS/App -I../GNSS/Target -I../Drivers/BSP/STM32WLxx_Nucleo -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-teseo_liv3f

clean-Drivers-2f-BSP-2f-Components-2f-teseo_liv3f:
	-$(RM) ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f.d ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f.o ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f.su ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_i2c.d ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_i2c.o ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_i2c.su ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_queue.d ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_queue.o ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_queue.su ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_uart.d ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_uart.o ./Drivers/BSP/Components/teseo_liv3f/teseo_liv3f_uart.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-teseo_liv3f

