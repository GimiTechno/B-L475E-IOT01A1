################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_api.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_calibration.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_core.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_ranging.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_strings.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_platform.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_platform_log.c \
../Core/Src/APP/BSP/vl53l0x/vl53l0x_proximity.c 

OBJS += \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_calibration.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_core.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_ranging.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_strings.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_platform.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_platform_log.o \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_proximity.o 

C_DEPS += \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_calibration.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_core.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_ranging.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_api_strings.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_platform.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_platform_log.d \
./Core/Src/APP/BSP/vl53l0x/vl53l0x_proximity.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/APP/BSP/vl53l0x/vl53l0x_api.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_api.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_api.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_api_calibration.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_calibration.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_api_calibration.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_api_core.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_core.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_api_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_api_ranging.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_ranging.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_api_ranging.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_api_strings.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_api_strings.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_api_strings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_platform.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_platform.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_platform.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_platform_log.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_platform_log.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_platform_log.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/APP/BSP/vl53l0x/vl53l0x_proximity.o: ../Core/Src/APP/BSP/vl53l0x/vl53l0x_proximity.c Core/Src/APP/BSP/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"Core/Src/APP/BSP/vl53l0x/vl53l0x_proximity.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

