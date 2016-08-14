################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DeviceControllers/BramController.c \
../src/DeviceControllers/IntrController.c \
../src/DeviceControllers/LcdController.c \
../src/DeviceControllers/UartContoller.c 

OBJS += \
./src/DeviceControllers/BramController.o \
./src/DeviceControllers/IntrController.o \
./src/DeviceControllers/LcdController.o \
./src/DeviceControllers/UartContoller.o 

C_DEPS += \
./src/DeviceControllers/BramController.d \
./src/DeviceControllers/IntrController.d \
./src/DeviceControllers/LcdController.d \
./src/DeviceControllers/UartContoller.d 


# Each subdirectory must supply rules for building sources it contributes
src/DeviceControllers/%.o: ../src/DeviceControllers/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../mBlaze_v1.3_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


