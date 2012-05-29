################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC/TFC_USB_CDC/driver/usb_driver.c" \

C_SRCS += \
../Sources/TFC/TFC_USB_CDC/driver/usb_driver.c \

OBJS += \
./Sources/TFC/TFC_USB_CDC/driver/usb_driver.obj \

OBJS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/driver/usb_driver.obj" \

C_DEPS += \
./Sources/TFC/TFC_USB_CDC/driver/usb_driver.d \

C_DEPS_QUOTED += \
"./Sources/TFC/TFC_USB_CDC/driver/usb_driver.d" \

OBJS_OS_FORMAT += \
./Sources/TFC/TFC_USB_CDC/driver/usb_driver.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC/TFC_USB_CDC/driver/usb_driver.obj: ../Sources/TFC/TFC_USB_CDC/driver/usb_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_USB_CDC/driver/usb_driver.args" -o "Sources/TFC/TFC_USB_CDC/driver/usb_driver.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_USB_CDC/driver/%.d: ../Sources/TFC/TFC_USB_CDC/driver/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


