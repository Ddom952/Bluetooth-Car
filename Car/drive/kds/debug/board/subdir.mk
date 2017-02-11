################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/V\ Semestr/Project/Projects/drive/board.c \
D:/V\ Semestr/Project/Projects/drive/clock_config.c \
D:/V\ Semestr/Project/Projects/drive/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/board.o: D:/V\ Semestr/Project/Projects/drive/board.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"board/board.d" -MT"board/board.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/clock_config.o: D:/V\ Semestr/Project/Projects/drive/clock_config.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"board/clock_config.d" -MT"board/clock_config.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

board/pin_mux.o: D:/V\ Semestr/Project/Projects/drive/pin_mux.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"board/pin_mux.d" -MT"board/pin_mux.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


