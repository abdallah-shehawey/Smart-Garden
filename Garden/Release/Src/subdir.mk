################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC_prog.c \
../Src/CLCD_prog.c \
../Src/DIO_prog.c \
../Src/EEPROM_prog.c \
../Src/EXTI_prog.c \
../Src/GIE_prog.c \
../Src/Garden.c \
../Src/LDR_prog.c \
../Src/LM35_prog.c \
../Src/SECURITY_prog.c \
../Src/Servo_Motor_prog.c \
../Src/System_init.c \
../Src/TIMER_program.c \
../Src/USART_prog.c 

OBJS += \
./Src/ADC_prog.o \
./Src/CLCD_prog.o \
./Src/DIO_prog.o \
./Src/EEPROM_prog.o \
./Src/EXTI_prog.o \
./Src/GIE_prog.o \
./Src/Garden.o \
./Src/LDR_prog.o \
./Src/LM35_prog.o \
./Src/SECURITY_prog.o \
./Src/Servo_Motor_prog.o \
./Src/System_init.o \
./Src/TIMER_program.o \
./Src/USART_prog.o 

C_DEPS += \
./Src/ADC_prog.d \
./Src/CLCD_prog.d \
./Src/DIO_prog.d \
./Src/EEPROM_prog.d \
./Src/EXTI_prog.d \
./Src/GIE_prog.d \
./Src/Garden.d \
./Src/LDR_prog.d \
./Src/LM35_prog.d \
./Src/SECURITY_prog.d \
./Src/Servo_Motor_prog.d \
./Src/System_init.d \
./Src/TIMER_program.d \
./Src/USART_prog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


