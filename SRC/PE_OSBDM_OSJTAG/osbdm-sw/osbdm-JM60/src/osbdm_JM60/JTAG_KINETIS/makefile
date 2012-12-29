################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 16
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(Gnu_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/USB_Drv/subdir.mk
-include Project\ Settings/Startup\ Code/subdir.mk
-include Project\ Settings/Linker\ Files/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
osbdm-jm60_kinetis.abs \

EXECUTABLES_QUOTED += \
"osbdm-jm60_kinetis.abs" \

EXECUTABLES_OS_FORMAT += \
osbdm-jm60_kinetis.abs \

BURNER_OUTPUT_OUTPUTS += \
osbdm-jm60_kinetis.abs.s19 \

BURNER_OUTPUT_OUTPUTS_QUOTED += \
"osbdm-jm60_kinetis.abs.s19" \

BURNER_OUTPUT_OUTPUTS_OS_FORMAT += \
osbdm-jm60_kinetis.abs.s19 \


# All Target
call-burner := 0
ifneq ($(strip $(EXECUTABLES)),)
ifneq ($(strip $(BBL_SRCS_QUOTED)),)
call-burner := 1
endif
endif
ifeq ($(call-burner),1)
all: osbdm-jm60_kinetis.abs osbdm-jm60_kinetis.abs.s19
else
all: osbdm-jm60_kinetis.abs
endif

# Tool invocations
osbdm-jm60_kinetis.abs: $(OBJS) $(USER_OBJS) C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/prm/Project.prm
	@echo 'Building target: $@'
	@echo 'Executing target #17 $@'
	@echo 'Invoking: S08 Linker'
	"$(HC08ToolsEnv)/linker" -ArgFile"osbdm-jm60_kinetis.args" -O"osbdm-jm60_kinetis.abs"
	@echo 'Finished building target: $@'
	@echo ' '

osbdm-jm60_kinetis.abs.s19: $(BBL_SRCS) $(EXECUTABLES)
	@echo 'Executing target #18 $@'
	@echo 'Invoking: S08 Burner'
	"$(HC08ToolsEnv)/burner" -ArgFile"osbdm-jm60_kinetis.abs.args" -f="$<" -env"ABS_FILE=$(strip $(EXECUTABLES_OS_FORMAT))"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) "./*/*/*.obj" "./*/*.obj"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(CXX_DEPS_QUOTED) $(BURNER_OUTPUT_OUTPUTS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*.d"  osbdm-jm60_kinetis.abs
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
