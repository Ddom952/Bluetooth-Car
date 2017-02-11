################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/system_MK64F12.c 

S_UPPER_SRCS += \
D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/gcc/startup_MK64F12.S 

OBJS += \
./startup/startup_MK64F12.o \
./startup/system_MK64F12.o 

C_DEPS += \
./startup/system_MK64F12.d 

S_UPPER_DEPS += \
./startup/startup_MK64F12.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_MK64F12.o: D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/gcc/startup_MK64F12.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -x assembler-with-cpp -DDEBUG -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mapcs  -std=gnu99 -MMD -MP -MF"startup/startup_MK64F12.d" -MT"startup/startup_MK64F12.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/system_MK64F12.o: D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/system_MK64F12.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"startup/system_MK64F12.d" -MT"startup/system_MK64F12.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


