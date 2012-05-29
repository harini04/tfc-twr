################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.c" \
"../Sources/TFC/TFC_USB_CDC/cdc/virtual_com.c" \

C_SRCS += \
../Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.c \
../Sources/TFC/TFC_USB_CDC/cdc/virtual_com.c \

OBJS += \
./Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.obj \
./Sources/TFC/TFC_USB_CDC/cdc/virtual_com.obj \

OBJS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.obj" \
"./Sources/TFC/TFC_USB_CDC/cdc/virtual_com.obj" \

C_DEPS += \
./Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.d \
./Sources/TFC/TFC_USB_CDC/cdc/virtual_com.d \

C_DEPS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.d" \
"./Sources/TFC/TFC_USB_CDC/cdc/virtual_com.d" \

OBJS_OS_FORMAT += \
./Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.obj \
./Sources/TFC/TFC_USB_CDC/cdc/virtual_com.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.obj: ../Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.args" -o "Sources/TFC/TFC_USB_CDC/cdc/usb_descriptor.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_USB_CDC/cdc/%.d: ../Sources/TFC/TFC_USB_CDC/cdc/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/TFC/TFC_USB_CDC/cdc/virtual_com.obj: ../Sources/TFC/TFC_USB_CDC/cdc/virtual_com.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/cdc/virtual_com.args" -o "Sources/TFC/TFC_USB_CDC/cdc/virtual_com.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


