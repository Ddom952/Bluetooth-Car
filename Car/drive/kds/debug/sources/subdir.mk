################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/V\ Semestr/Project/Projects/drive/command_decoder.c \
D:/V\ Semestr/Project/Projects/drive/drive.c \
D:/V\ Semestr/Project/Projects/drive/main.c \
D:/V\ Semestr/Project/Projects/drive/my_string.c \
D:/V\ Semestr/Project/Projects/drive/uart.c 

OBJS += \
./sources/command_decoder.o \
./sources/drive.o \
./sources/main.o \
./sources/my_string.o \
./sources/uart.o 

C_DEPS += \
./sources/command_decoder.d \
./sources/drive.d \
./sources/main.d \
./sources/my_string.d \
./sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
sources/command_decoder.o: D:/V\ Semestr/Project/Projects/drive/command_decoder.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"sources/command_decoder.d" -MT"sources/command_decoder.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sources/drive.o: D:/V\ Semestr/Project/Projects/drive/drive.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"sources/drive.d" -MT"sources/drive.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sources/main.o: D:/V\ Semestr/Project/Projects/drive/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"sources/main.d" -MT"sources/main.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sources/my_string.o: D:/V\ Semestr/Project/Projects/drive/my_string.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"sources/my_string.d" -MT"sources/my_string.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

sources/uart.o: D:/V\ Semestr/Project/Projects/drive/uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"sources/uart.d" -MT"sources/uart.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


