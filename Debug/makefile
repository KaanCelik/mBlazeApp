################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include src/Utilities/subdir.mk
-include src/DeviceControllers/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
ITU_uBlaze.elf.size \

ELFCHECK += \
ITU_uBlaze.elf.elfcheck \


# All Target
all: ITU_uBlaze.elf secondary-outputs

# Tool invocations
ITU_uBlaze.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../mBlaze_v1.3_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.a -mno-xl-soft-mul -o"ITU_uBlaze.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

ITU_uBlaze.elf.size: ITU_uBlaze.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size ITU_uBlaze.elf  |tee "ITU_uBlaze.elf.size"
	@echo Finished building: $@
	@echo ' '

ITU_uBlaze.elf.elfcheck: ITU_uBlaze.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck ITU_uBlaze.elf -hw ../../mBlaze2_hw_platform/system.xml -pe microblaze_0  |tee "ITU_uBlaze.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) ITU_uBlaze.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
