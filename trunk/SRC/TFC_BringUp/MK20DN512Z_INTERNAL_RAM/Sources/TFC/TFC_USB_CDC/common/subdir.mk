################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC/TFC_USB_CDC/common/usb_class.c" \
"../Sources/TFC/TFC_USB_CDC/common/usb_framework.c" \

C_SRCS += \
../Sources/TFC/TFC_USB_CDC/common/usb_class.c \
../Sources/TFC/TFC_USB_CDC/common/usb_framework.c \

OBJS += \
./Sources/TFC/TFC_USB_CDC/common/usb_class.obj \
./Sources/TFC/TFC_USB_CDC/common/usb_framework.obj \

OBJS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/common/usb_class.obj" \
"./Sources/TFC/TFC_USB_CDC/common/usb_framework.obj" \

C_DEPS += \
./Sources/TFC/TFC_USB_CDC/common/usb_class.d \
./Sources/TFC/TFC_USB_CDC/common/usb_framework.d \

C_DEPS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/common/usb_class.d" \
"./Sources/TFC/TFC_USB_CDC/common/usb_framework.d" \

OBJS_OS_FORMAT += \
./Sources/TFC/TFC_USB_CDC/common/usb_class.obj \
./Sources/TFC/TFC_USB_CDC/common/usb_framework.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC/TFC_USB_CDC/common/usb_class.obj: ../Sources/TFC/TFC_USB_CDC/common/usb_class.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/common/usb_class.args" -o "Sources/TFC/TFC_USB_CDC/common/usb_class.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_USB_CDC/common/%.d: ../Sources/TFC/TFC_USB_CDC/common/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/TFC/TFC_USB_CDC/common/usb_framework.obj: ../Sources/TFC/TFC_USB_CDC/common/usb_framework.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/common/usb_framework.args" -o "Sources/TFC/TFC_USB_CDC/common/usb_framework.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


