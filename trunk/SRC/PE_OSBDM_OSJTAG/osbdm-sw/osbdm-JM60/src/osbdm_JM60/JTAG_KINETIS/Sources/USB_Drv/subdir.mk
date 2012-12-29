################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Descriptor.c" \
"C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Drv.c" \
"C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Ep0_Handler.c" \

C_SRCS += \
C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Descriptor.c \
C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Drv.c \
C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Ep0_Handler.c \

OBJS += \
./Sources/USB_Drv/Usb_Descriptor_c.obj \
./Sources/USB_Drv/Usb_Drv_c.obj \
./Sources/USB_Drv/Usb_Ep0_Handler_c.obj \

OBJS_QUOTED += \
"./Sources/USB_Drv/Usb_Descriptor_c.obj" \
"./Sources/USB_Drv/Usb_Drv_c.obj" \
"./Sources/USB_Drv/Usb_Ep0_Handler_c.obj" \

C_DEPS += \
./Sources/USB_Drv/Usb_Descriptor_c.d \
./Sources/USB_Drv/Usb_Drv_c.d \
./Sources/USB_Drv/Usb_Ep0_Handler_c.d \

C_DEPS_QUOTED += \
"./Sources/USB_Drv/Usb_Descriptor_c.d" \
"./Sources/USB_Drv/Usb_Drv_c.d" \
"./Sources/USB_Drv/Usb_Ep0_Handler_c.d" \

OBJS_OS_FORMAT += \
./Sources/USB_Drv/Usb_Descriptor_c.obj \
./Sources/USB_Drv/Usb_Drv_c.obj \
./Sources/USB_Drv/Usb_Ep0_Handler_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/USB_Drv/Usb_Descriptor_c.obj: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Descriptor.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/USB_Drv/Usb_Descriptor.args" -ObjN="Sources/USB_Drv/Usb_Descriptor_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/USB_Drv/Usb_Descriptor_c.d: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Descriptor.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/USB_Drv/Usb_Drv_c.obj: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Drv.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/USB_Drv/Usb_Drv.args" -ObjN="Sources/USB_Drv/Usb_Drv_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/USB_Drv/Usb_Drv_c.d: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Drv.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/USB_Drv/Usb_Ep0_Handler_c.obj: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Ep0_Handler.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/USB_Drv/Usb_Ep0_Handler.args" -ObjN="Sources/USB_Drv/Usb_Ep0_Handler_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/USB_Drv/Usb_Ep0_Handler_c.d: C:/Users/EHUGHES/Desktop/osbdm_pemicro/osbdm-sw/osbdm-JM60/src/Usb_Drv/Usb_Ep0_Handler.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


