#include "TFC\TFC.h"

/**********************************************************************************************
 *  
 *  This file sets up the Pulse Width Modulation Timer Module for use by a servo.  It is set 
 *  to utilize Edge-Aligned PWM, and this file properly configures the period, and pulse width 
 *  for use by the other modules
 *  a
 *  Several important functions are contained in this file:
 *  1. Init_PWM_Servo () - initializes the timer module 
 *  2. PWM_Servo (double duty_Cycle) - enter the desired duty cycle setting for the servo
 *  3. Servo_Tick - interrupt routine which executes once/servo period
 *  
 *  	
 *  
 * **********  DETAILS *****************
 * 
 *
 * EDGE-Aligned PWM:  selected when QUADEN=0, DECAPEN=0, COMBINE=0, CPWMS=0, and MSnB=1  
 * For typical Servo operation set period to:  20 ms, vary pulse width between .5ms and 1.5ms to set steering angle
 * 
 * Period on chip determined by MOD-CNTIN +0x0001 
 * Pulse width determined by (CnV-CNTIN)  
 * 
 * - see Edge-Aligned PWM (EPWM) Mode in reference manual for details
 * 
 **********************************************************************************************/


#define FTM1_CLK_PRESCALE			6  // Prescale Selector value - see comments in Status Control (SC) section for more details
#define FTM1_OVERFLOW_FREQUENCY 	50  // Desired Frequency of PWM Signal - Here 50Hz => 20ms period
// use these to dial in servo steering to your particular servo
#define SERVO0_MIN_DUTY_CYCLE			(float)(.0005*FTM1_OVERFLOW_FREQUENCY)  // The number here should be be *pulse width* in seconds to move servo to its left limit
#define SERVO0_MAX_DUTY_CYCLE  			(float)(.0020*FTM1_OVERFLOW_FREQUENCY)  // The number here should be be *pulse width* in seconds to move servo to its Right limit
/**********************************************************************************************/

//Position is -1.0 to 1.0.   Use SERVO_X_MIN_DUTY_CYCLE and SERVO_MAX_DUTY_CYCLE  to calibrate the extremes
void TFC_SetServo(uint8_t ServoNumber, float Position)
{
		TFC_SetServoDutyCycle(ServoNumber , 
				(((Position + 1.0)/2)*(SERVO0_MAX_DUTY_CYCLE - SERVO0_MIN_DUTY_CYCLE))+SERVO0_MIN_DUTY_CYCLE);
	
}

void TFC_SetServoDutyCycle(uint8_t ServoNumber, float DutyCycle)
{
	 switch(ServoNumber)
	 {
	 default:
	 case 0:
		 FTM1_C0V = FTM1_MOD  * DutyCycle;
		break;

	 case 1:
		 FTM1_C1V = FTM1_MOD  * DutyCycle;
		 break;
	 }
}

/******************************************* Function to control Interrupt ************************************/
volatile unsigned char ServoTickVar;

void ServoTickIrq()
{
	if (ServoTickVar < 0xff)//if servo tick less than 255 count up... 
		ServoTickVar++;
	//Clear the overflow mask if set
		if(FTM1_SC & FTM_SC_TOF_MASK)
			FTM1_SC &= ~FTM_SC_TOF_MASK;
}

void TFC_InitServos()
{

	//Enable the Clock to the FTM0 Module
	SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK; 
	
	//Enable CLock to Port B so the Timer can get out.
		
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	//Pin control Register (MUX allowing user to route the desired signal to the pin.  
	PORTB_PCR0  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK;
	PORTB_PCR1  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK;

	//FTM0_MODE[WPDIS] = 1; //Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.  
	FTM1_MODE |= FTM_MODE_WPDIS_MASK;

	//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
	FTM1_MODE &= ~FTM_MODE_FTMEN_MASK; 

	//Set Edge Aligned PWM
	FTM1_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;  
	//QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)

	// Also need to setup the FTM0C0SC channel control register 
	FTM1_CNT = 0x0; //FTM Counter Value - reset counter to zero
	FTM1_MOD = (PERIPHERAL_BUS_CLOCK/(1<<FTM1_CLK_PRESCALE))/FTM1_OVERFLOW_FREQUENCY ;  // Count value of full duty cycle
	FTM1_CNTIN = 0; //Set the Counter Initial Value to 0 

	// FTMx_CnSC - contains the channel-interrupt status flag control bits
	FTM1_C0SC |= FTM_CnSC_ELSB_MASK; //Edge or level select
	FTM1_C0SC &= ~FTM_CnSC_ELSA_MASK; //Edge or level Select
	FTM1_C0SC |= FTM_CnSC_MSB_MASK; //Channel Mode select

	FTM1_C1SC |= FTM_CnSC_ELSB_MASK; //Edge or level select
	FTM1_C1SC &= ~FTM_CnSC_ELSA_MASK; //Edge or level Select
	FTM1_C1SC |= FTM_CnSC_MSB_MASK; //Channel Mode select
	
	//Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately
	FTM1_SC = 0; //Make sure its Off!

	// FTMx_CnV contains the captured FTM counter value, this value determines the pulse width
	FTM1_C0V = 0; 
	FTM1_C1V = 0; 

	//Status and Control bits 
	FTM1_SC =  FTM_SC_CLKS(1); // Selects Clock source to be "system clock" or (01) 

	FTM1_SC |= FTM_SC_PS(FTM1_CLK_PRESCALE); //sets pre-scale value see details below

	
	// Interrupts
//	FTM1_SC |= FTM_SC_TOIE_MASK; //Enable the interrupt mask.  timer overflow interrupt.. enables interrupt signal to come out of the module itself...  (have to enable 2x, one in the peripheral and once in the NVIC
//	enable_irq(INT_FTM1-16);  // Set NVIC location, but you still have to change/check NVIC file sysinit.c under Project Settings Folder	
}