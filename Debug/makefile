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
FirstProject.elf.size \

ELFCHECK += \
FirstProject.elf.elfcheck \


# All Target
all: FirstProject.elf secondary-outputs

# Tool invocations
FirstProject.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../mBlaze_v1.2.1_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.a -mno-xl-soft-mul -o"FirstProject.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

FirstProject.elf.size: FirstProject.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size FirstProject.elf  |tee "FirstProject.elf.size"
	@echo Finished building: $@
	@echo ' '

FirstProject.elf.elfcheck: FirstProject.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck FirstProject.elf -hw ../../mBlaze2_hw_platform/system.xml -pe microblaze_0  |tee "FirstProject.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) FirstProject.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
