################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../PWM.c \
../Timer1.c \
../external_eeprom.c \
../gpio.c \
../main.c \
../motor.c \
../twi.c \
../uart.c 

OBJS += \
./Buzzer.o \
./PWM.o \
./Timer1.o \
./external_eeprom.o \
./gpio.o \
./main.o \
./motor.o \
./twi.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./PWM.d \
./Timer1.d \
./external_eeprom.d \
./gpio.d \
./main.d \
./motor.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


