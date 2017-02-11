################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_debug_console.c \
D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_notifier.c \
D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_sbrk.c \
D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_shell.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_notifier.o \
./utilities/fsl_sbrk.o \
./utilities/fsl_shell.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_notifier.d \
./utilities/fsl_sbrk.d \
./utilities/fsl_shell.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/fsl_debug_console.o: D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_debug_console.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"utilities/fsl_debug_console.d" -MT"utilities/fsl_debug_console.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/fsl_notifier.o: D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_notifier.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"utilities/fsl_notifier.d" -MT"utilities/fsl_notifier.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/fsl_sbrk.o: D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_sbrk.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"utilities/fsl_sbrk.d" -MT"utilities/fsl_sbrk.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/fsl_shell.o: D:/V\ Semestr/Project/Projects/drive/devices/MK64F12/utilities/fsl_shell.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DFSL_RTOS_BM -DCPU_MK64FN1M0VLL12 -DNDEBUG -I../../ -I../../devices/MK64F12 -I../../devices/MK64F12/utilities -I../../devices/MK64F12/drivers -I../../devices/MK64F12/gcc -I../../CMSIS/Include -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"utilities/fsl_shell.d" -MT"utilities/fsl_shell.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


