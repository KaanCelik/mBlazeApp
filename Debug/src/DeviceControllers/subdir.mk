################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DeviceControllers/AxiTimerController.c \
../src/DeviceControllers/IntrController.c 

OBJS += \
./src/DeviceControllers/AxiTimerController.o \
./src/DeviceControllers/IntrController.o 

C_DEPS += \
./src/DeviceControllers/AxiTimerController.d \
./src/DeviceControllers/IntrController.d 


# Each subdirectory must supply rules for building sources it contributes
src/DeviceControllers/%.o: ../src/DeviceControllers/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../mBlaze_v1.2.1/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


