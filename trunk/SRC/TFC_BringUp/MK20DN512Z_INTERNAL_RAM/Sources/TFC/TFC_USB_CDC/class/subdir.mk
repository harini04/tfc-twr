################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC/TFC_USB_CDC/class/usb_cdc.c" \
"../Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.c" \

C_SRCS += \
../Sources/TFC/TFC_USB_CDC/class/usb_cdc.c \
../Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.c \

OBJS += \
./Sources/TFC/TFC_USB_CDC/class/usb_cdc.obj \
./Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.obj \

OBJS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/class/usb_cdc.obj" \
"./Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.obj" \

C_DEPS += \
./Sources/TFC/TFC_USB_CDC/class/usb_cdc.d \
./Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.d \

C_DEPS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/class/usb_cdc.d" \
"./Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.d" \

OBJS_OS_FORMAT += \
./Sources/TFC/TFC_USB_CDC/class/usb_cdc.obj \
./Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC/TFC_USB_CDC/class/usb_cdc.obj: ../Sources/TFC/TFC_USB_CDC/class/usb_cdc.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/class/usb_cdc.args" -o "Sources/TFC/TFC_USB_CDC/class/usb_cdc.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_USB_CDC/class/%.d: ../Sources/TFC/TFC_USB_CDC/class/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.obj: ../Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.args" -o "Sources/TFC/TFC_USB_CDC/class/usb_cdc_pstn.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


