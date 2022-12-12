################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLCD_prog.c \
../DIO_prog.c \
../PORT_program.c \
../SD_prog.c \
../SPI_prog.c \
../USART_prog.c \
../main.c 

OBJS += \
./CLCD_prog.o \
./DIO_prog.o \
./PORT_program.o \
./SD_prog.o \
./SPI_prog.o \
./USART_prog.o \
./main.o 

C_DEPS += \
./CLCD_prog.d \
./DIO_prog.d \
./PORT_program.d \
./SD_prog.d \
./SPI_prog.d \
./USART_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


