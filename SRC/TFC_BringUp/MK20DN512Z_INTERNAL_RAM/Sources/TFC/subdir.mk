################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC/TFC.c" \
"../Sources/TFC/TFC_ADC.c" \
"../Sources/TFC/TFC_ARM_SysTick.c" \
"../Sources/TFC/TFC_BoardSupport.c" \
"../Sources/TFC/TFC_CrystalClock.c" \
"../Sources/TFC/TFC_LineScanCamera.c" \
"../Sources/TFC/TFC_NTSC.c" \
"../Sources/TFC/TFC_PWM_Motor.c" \
"../Sources/TFC/TFC_PWM_Servo.c" \
"../Sources/TFC/TFC_Potentiometer.c" \
"../Sources/TFC/TFC_Queue.c" \
"../Sources/TFC/TFC_Terminal.c" \
"../Sources/TFC/TFC_UART.c" \
"../Sources/TFC/TFC_arm_cm4.c" \

C_SRCS += \
../Sources/TFC/TFC.c \
../Sources/TFC/TFC_ADC.c \
../Sources/TFC/TFC_ARM_SysTick.c \
../Sources/TFC/TFC_BoardSupport.c \
../Sources/TFC/TFC_CrystalClock.c \
../Sources/TFC/TFC_LineScanCamera.c \
../Sources/TFC/TFC_NTSC.c \
../Sources/TFC/TFC_PWM_Motor.c \
../Sources/TFC/TFC_PWM_Servo.c \
../Sources/TFC/TFC_Potentiometer.c \
../Sources/TFC/TFC_Queue.c \
../Sources/TFC/TFC_Terminal.c \
../Sources/TFC/TFC_UART.c \
../Sources/TFC/TFC_arm_cm4.c \

OBJS += \
./Sources/TFC/TFC.obj \
./Sources/TFC/TFC_ADC.obj \
./Sources/TFC/TFC_ARM_SysTick.obj \
./Sources/TFC/TFC_BoardSupport.obj \
./Sources/TFC/TFC_CrystalClock.obj \
./Sources/TFC/TFC_LineScanCamera.obj \
./Sources/TFC/TFC_NTSC.obj \
./Sources/TFC/TFC_PWM_Motor.obj \
./Sources/TFC/TFC_PWM_Servo.obj \
./Sources/TFC/TFC_Potentiometer.obj \
./Sources/TFC/TFC_Queue.obj \
./Sources/TFC/TFC_Terminal.obj \
./Sources/TFC/TFC_UART.obj \
./Sources/TFC/TFC_arm_cm4.obj \

OBJS_QUOTED += \
"./Sources/TFC/TFC.obj" \
"./Sources/TFC/TFC_ADC.obj" \
"./Sources/TFC/TFC_ARM_SysTick.obj" \
"./Sources/TFC/TFC_BoardSupport.obj" \
"./Sources/TFC/TFC_CrystalClock.obj" \
"./Sources/TFC/TFC_LineScanCamera.obj" \
"./Sources/TFC/TFC_NTSC.obj" \
"./Sources/TFC/TFC_PWM_Motor.obj" \
"./Sources/TFC/TFC_PWM_Servo.obj" \
"./Sources/TFC/TFC_Potentiometer.obj" \
"./Sources/TFC/TFC_Queue.obj" \
"./Sources/TFC/TFC_Terminal.obj" \
"./Sources/TFC/TFC_UART.obj" \
"./Sources/TFC/TFC_arm_cm4.obj" \

C_DEPS += \
./Sources/TFC/TFC.d \
./Sources/TFC/TFC_ADC.d \
./Sources/TFC/TFC_ARM_SysTick.d \
./Sources/TFC/TFC_BoardSupport.d \
./Sources/TFC/TFC_CrystalClock.d \
./Sources/TFC/TFC_LineScanCamera.d \
./Sources/TFC/TFC_NTSC.d \
./Sources/TFC/TFC_PWM_Motor.d \
./Sources/TFC/TFC_PWM_Servo.d \
./Sources/TFC/TFC_Potentiometer.d \
./Sources/TFC/TFC_Queue.d \
./Sources/TFC/TFC_Terminal.d \
./Sources/TFC/TFC_UART.d \
./Sources/TFC/TFC_arm_cm4.d \

C_DEPS_QUOTED += \
"./Sources/TFC/TFC.d" \
"./Sources/TFC/TFC_ADC.d" \
"./Sources/TFC/TFC_ARM_SysTick.d" \
"./Sources/TFC/TFC_BoardSupport.d" \
"./Sources/TFC/TFC_CrystalClock.d" \
"./Sources/TFC/TFC_LineScanCamera.d" \
"./Sources/TFC/TFC_NTSC.d" \
"./Sources/TFC/TFC_PWM_Motor.d" \
"./Sources/TFC/TFC_PWM_Servo.d" \
"./Sources/TFC/TFC_Potentiometer.d" \
"./Sources/TFC/TFC_Queue.d" \
"./Sources/TFC/TFC_Terminal.d" \
"./Sources/TFC/TFC_UART.d" \
"./Sources/TFC/TFC_arm_cm4.d" \

OBJS_OS_FORMAT += \
./Sources/TFC/TFC.obj \
./Sources/TFC/TFC_ADC.obj \
./Sources/TFC/TFC_ARM_SysTick.obj \
./Sources/TFC/TFC_BoardSupport.obj \
./Sources/TFC/TFC_CrystalClock.obj \
./Sources/TFC/TFC_LineScanCamera.obj \
./Sources/TFC/TFC_NTSC.obj \
./Sources/TFC/TFC_PWM_Motor.obj \
./Sources/TFC/TFC_PWM_Servo.obj \
./Sources/TFC/TFC_Potentiometer.obj \
./Sources/TFC/TFC_Queue.obj \
./Sources/TFC/TFC_Terminal.obj \
./Sources/TFC/TFC_UART.obj \
./Sources/TFC/TFC_arm_cm4.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC/TFC.obj: ../Sources/TFC/TFC.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC.args" -o "Sources/TFC/TFC.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/%.d: ../Sources/TFC/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/TFC/TFC_ADC.obj: ../Sources/TFC/TFC_ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_ADC.args" -o "Sources/TFC/TFC_ADC.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_ARM_SysTick.obj: ../Sources/TFC/TFC_ARM_SysTick.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_ARM_SysTick.args" -o "Sources/TFC/TFC_ARM_SysTick.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_BoardSupport.obj: ../Sources/TFC/TFC_BoardSupport.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_BoardSupport.args" -o "Sources/TFC/TFC_BoardSupport.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_CrystalClock.obj: ../Sources/TFC/TFC_CrystalClock.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_CrystalClock.args" -o "Sources/TFC/TFC_CrystalClock.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_LineScanCamera.obj: ../Sources/TFC/TFC_LineScanCamera.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_LineScanCamera.args" -o "Sources/TFC/TFC_LineScanCamera.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_NTSC.obj: ../Sources/TFC/TFC_NTSC.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_NTSC.args" -o "Sources/TFC/TFC_NTSC.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_PWM_Motor.obj: ../Sources/TFC/TFC_PWM_Motor.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_PWM_Motor.args" -o "Sources/TFC/TFC_PWM_Motor.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_PWM_Servo.obj: ../Sources/TFC/TFC_PWM_Servo.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_PWM_Servo.args" -o "Sources/TFC/TFC_PWM_Servo.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_Potentiometer.obj: ../Sources/TFC/TFC_Potentiometer.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_Potentiometer.args" -o "Sources/TFC/TFC_Potentiometer.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_Queue.obj: ../Sources/TFC/TFC_Queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_Queue.args" -o "Sources/TFC/TFC_Queue.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_Terminal.obj: ../Sources/TFC/TFC_Terminal.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_Terminal.args" -o "Sources/TFC/TFC_Terminal.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_UART.obj: ../Sources/TFC/TFC_UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_UART.args" -o "Sources/TFC/TFC_UART.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC/TFC_arm_cm4.obj: ../Sources/TFC/TFC_arm_cm4.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Compiler'
	"$(ARM_ToolsDirEnv)/mwccarm" -gccinc @@"Sources/TFC/TFC_arm_cm4.args" -o "Sources/TFC/TFC_arm_cm4.obj" -c "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


