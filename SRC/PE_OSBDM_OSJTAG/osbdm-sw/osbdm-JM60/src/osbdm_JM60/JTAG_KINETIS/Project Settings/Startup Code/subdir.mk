################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Start08.c" \

C_SRCS += \
C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Start08.c \

OBJS += \
./Project\ Settings/Startup\ Code/Start08_c.obj \

OBJS_QUOTED += \
"./Project Settings/Startup Code/Start08_c.obj" \

C_DEPS += \
./Project\ Settings/Startup\ Code/Start08_c.d \

C_DEPS_QUOTED += \
"./Project Settings/Startup Code/Start08_c.d" \

OBJS_OS_FORMAT += \
./Project\ Settings/Startup\ Code/Start08_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Project\ Settings/Startup\ Code/Start08_c.obj: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Start08.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Project Settings/Startup Code/Start08.args" -ObjN="Project Settings/Startup Code/Start08_c.obj" "$<" -Lm="Project Settings/Startup Code/Start08_c.d" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Project\ Settings/Startup\ Code/Start08_c.d: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Start08.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


