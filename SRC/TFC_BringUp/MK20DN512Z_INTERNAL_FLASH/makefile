################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 24
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(Gnu_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/TFC/subdir.mk
-include Sources/TFC/TFC_USB_CDC/driver/subdir.mk
-include Sources/TFC/TFC_USB_CDC/driver/kinetis/subdir.mk
-include Sources/TFC/TFC_USB_CDC/common/subdir.mk
-include Sources/TFC/TFC_USB_CDC/class/subdir.mk
-include Sources/TFC/TFC_USB_CDC/cdc/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TFC_BringUp.afx \

EXECUTABLES_QUOTED += \
"TFC_BringUp.afx" \

EXECUTABLES_OS_FORMAT += \
TFC_BringUp.afx \


# All Target
all: TFC_BringUp.afx

# Tool invocations
TFC_BringUp.afx: $(OBJS) $(LCF_BUILD_DEPENCENCY) $(USER_OBJS) $(LCF_SRCS)
	@echo 'Building target: $@'
	@echo 'Executing target #25 $@'
	@echo 'Invoking: ARM Linker'
	"$(ARM_ToolsDirEnv)/mwldarm" @@"TFC_BringUp.args" -o "TFC_BringUp.afx"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(CPP_DEPS_QUOTED) "./*/*/*.obj" "./*/*/*/*/*.obj" "./*/*/*/*/*/*.obj" "./*/*.obj"  $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*/*/*/*.d" "./*/*/*/*/*/*.d" "./*/*.d"  TFC_BringUp.afx
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
