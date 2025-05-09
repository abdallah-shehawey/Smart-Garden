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
../Src/System_init.c \
../Src/USART_prog.c \
../Src/main.c 

OBJS += \
./Src/ADC_prog.o \
./Src/CLCD_prog.o \
./Src/DIO_prog.o \
./Src/EEPROM_prog.o \
./Src/EXTI_prog.o \
./Src/GIE_prog.o \
./Src/System_init.o \
./Src/USART_prog.o \
./Src/main.o 

C_DEPS += \
./Src/ADC_prog.d \
./Src/CLCD_prog.d \
./Src/DIO_prog.d \
./Src/EEPROM_prog.d \
./Src/EXTI_prog.d \
./Src/GIE_prog.d \
./Src/System_init.d \
./Src/USART_prog.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


