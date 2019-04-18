################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/button.c \
../src/led.c \
../src/mpu.c \
../src/uart.c 

OBJS += \
./src/button.o \
./src/led.o \
./src/mpu.o \
./src/uart.o 

C_DEPS += \
./src/button.d \
./src/led.d \
./src/mpu.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -I"D:\intelFPGA\18.1\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"D:\intelFPGA\18.1\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"E:\2019InnovateFPGA\CODE_Project\Software\hello\hello\inc" -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


