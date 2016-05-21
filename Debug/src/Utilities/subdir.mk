################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Utilities/Util.c \
../src/Utilities/Vector.c 

OBJS += \
./src/Utilities/Util.o \
./src/Utilities/Vector.o 

C_DEPS += \
./src/Utilities/Util.d \
./src/Utilities/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utilities/%.o: ../src/Utilities/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../mBlaze_v1.2.1/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


