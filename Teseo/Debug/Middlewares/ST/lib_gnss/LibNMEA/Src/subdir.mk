################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/lib_gnss/LibNMEA/Src/NMEA_parser.c 

OBJS += \
./Middlewares/ST/lib_gnss/LibNMEA/Src/NMEA_parser.o 

C_DEPS += \
./Middlewares/ST/lib_gnss/LibNMEA/Src/NMEA_parser.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/lib_gnss/LibNMEA/Src/%.o Middlewares/ST/lib_gnss/LibNMEA/Src/%.su: ../Middlewares/ST/lib_gnss/LibNMEA/Src/%.c Middlewares/ST/lib_gnss/LibNMEA/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../GNSS/App -I../GNSS/Target -I../Drivers/BSP/STM32WLxx_Nucleo -I../Middlewares/ST/lib_gnss/LibGNSS/Inc -I../Middlewares/ST/lib_gnss/LibNMEA/Inc -I../Drivers/BSP/Components/teseo_liv3f -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-lib_gnss-2f-LibNMEA-2f-Src

clean-Middlewares-2f-ST-2f-lib_gnss-2f-LibNMEA-2f-Src:
	-$(RM) ./Middlewares/ST/lib_gnss/LibNMEA/Src/NMEA_parser.d ./Middlewares/ST/lib_gnss/LibNMEA/Src/NMEA_parser.o ./Middlewares/ST/lib_gnss/LibNMEA/Src/NMEA_parser.su

.PHONY: clean-Middlewares-2f-ST-2f-lib_gnss-2f-LibNMEA-2f-Src

