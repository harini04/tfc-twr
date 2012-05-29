################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.c" \

C_SRCS += \
../Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.c \

OBJS += \
./Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.obj \

OBJS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.obj" \

C_DEPS += \
./Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.d \

C_DEPS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.d" \

OBJS_OS_FORMAT += \
./Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.obj: ../Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.args" -o "Sources/TFC/TFC_USB_CDC/driver/kinetis/usb_dci_kinetis.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_USB_CDC/driver/kinetis/%.d: ../Sources/TFC/TFC_USB_CDC/driver/kinetis/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


