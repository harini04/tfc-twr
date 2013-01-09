/*
 * Pwm_Motor.c
 *
 *  USing 	Port B 0 (pwm)
 *  		Port B 1 (pwm compliment)
 *  
 *  	FTM1_CH0 PTC8 B68 PWM
 *  	FTM1_CH1 pta9
 *  
 *  This file sets up the Pulse Width Modulation Timer Module for use by other modules
 */
#include "TFC\TFC.h"
#include "Derivative.h"


#define FTM0_MOD_VALUE	(int)((float)(PERIPHERAL_BUS_CLOCK)/TFC_MOTOR_SWITCHING_FREQUENCY)
/*
void TFC_InitMotorPWM()
{
	
	//Enable the Clock to the FTM0 Module
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK; 
    
	//Enable CLock to Port C so the PWM can get out.
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	

    PORTC_PCR1  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;
    PORTC_PCR2  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;
    PORTC_PCR3  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;
    PORTC_PCR4  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;

    //FTM2_MODE[WPDIS] = 1; //Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.  
    FTM0_MODE |= FTM_MODE_WPDIS_MASK;
    
    //FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
   // FTM0_MODE |= FTM_MODE_FTMEN_MASK; 
    
  FTM0_CNT = 0x0; //FTM Counter Value - (initialize the CNT before writing to MOD)  (16 bit available - bits 0-15 are count)
  FTM0_MOD = FTM0_MOD_VALUE; //Set the Modulo resister (16 bit available - bits 0-15), Mod is set to 24000
  FTM0_CNTIN = 0; //Set the Counter Initial Value to 0   (pg 915)
  
   
  //We want complementary mode out put.   2 outputs to Channel N and N+1 where N+1 is inverter to drive the H-BRIDGE
  
  //37.4.9 Complementary Mode
 // The complementary mode is selected when (FTMEN = 1), (QUADEN = 0), (DECAPEN= 0), (COMBINE = 1), (CPWMS = 0), and (COMP = 1).
 //                                       
 // In complementary mode the channel (n+1) output is the inverse of the channel (n) output.
 // If (FTMEN = 1), (QUADEN = 0), (DECAPEN = 0), (COMBINE = 1), (CPWMS = 0),
 // and (COMP = 0), then the channel (n+1) output is the same as the channel (n) output.
  
  //QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)
  FTM0_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;  
  
  //Set CPWMS to zero 
  FTM0_SC &=~FTM_SC_CPWMS_MASK;
  
  //Set DECAPEN for channel 0
  FTM0_COMBINE &= ~FTM_COMBINE_DECAPEN0_MASK;
  //Set DECAPEN for channel 0
  FTM0_COMBINE &= ~FTM_COMBINE_DECAPEN2_MASK;;
		  
    
  //Combine Channels 0 and 1
  FTM0_COMBINE |= FTM_COMBINE_COMBINE0_MASK;
  //Combine Channels 2 and 3
  FTM0_COMBINE |= FTM_COMBINE_COMBINE1_MASK;
  
  //Make Channels 0 and 1 Complementary
  FTM0_COMBINE |= FTM_COMBINE_COMP0_MASK;
  //Make Channels 0 and 1 Complementary
  FTM0_COMBINE |= FTM_COMBINE_COMP1_MASK;
  

  
  FTM0_C0SC |= FTM_CnSC_MSB_MASK;
  FTM0_C1SC |= FTM_CnSC_MSB_MASK;
  FTM0_C2SC |= FTM_CnSC_MSB_MASK;
  FTM0_C3SC |= FTM_CnSC_MSB_MASK;
    
  //Low-true pulses clear on channel (n) match, and set on channel (n+1) match)
  FTM0_C0SC |= FTM_CnSC_ELSA_MASK;
  FTM0_C0SC &= ~FTM_CnSC_ELSB_MASK;
  //Low-true pulses clear on channel (n) match, and set on channel (n+1) match)
  FTM0_C1SC |= FTM_CnSC_ELSA_MASK;
  FTM0_C1SC &= ~FTM_CnSC_ELSB_MASK;
  //Low-true pulses clear on channel (n) match, and set on channel (n+1) match)
  FTM0_C2SC |= FTM_CnSC_ELSA_MASK;
  FTM0_C2SC &= ~FTM_CnSC_ELSB_MASK;
  //Low-true pulses clear on channel (n) match, and set on channel (n+1) match)
  FTM0_C3SC |= FTM_CnSC_ELSA_MASK;
  FTM0_C3SC &= ~FTM_CnSC_ELSB_MASK;
  
  FTM0_C0V = FTM0_MOD_VALUE/2; //Set the Channel 0/1 Value to 50%
  FTM0_C1V = FTM0_MOD_VALUE/2; //Set the Channel 0/1 Value to 50%
  FTM0_C2V = FTM0_MOD_VALUE/2; //Set the Channel 0/1 Value to 50%
  FTM0_C3V = FTM0_MOD_VALUE/2; //Set the Channel 0/1 Value to 50%
  
  //FTM0_PWMLOAD =  FTM_PWMLOAD_CH0SEL_MASK | 
//				  FTM_PWMLOAD_CH1SEL_MASK |
//				  FTM_PWMLOAD_CH2SEL_MASK |
//				  FTM_PWMLOAD_CH3SEL_MASK;
  
  FTM0_SC = FTM_SC_PS(0) | FTM_SC_CLKS(1);  
}
*/
void TFC_InitMotorPWM()
{
	
	//Enable the Clock to the FTM0 Module
		SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK; 
	    
		//Enable CLock to Port C so the PWM can get out.
		SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
		

	    PORTC_PCR1  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;
	    PORTC_PCR2  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;
	    PORTC_PCR3  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;
	    PORTC_PCR4  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;

//ECAPEN=0, COMBINE=0, CPWMS=0, and MSnB=1  (page 964)
// Properly set up Flex Timer Module

//FTM2_MODE[WPDIS] = 1; //Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.  
FTM0_MODE |= FTM_MODE_WPDIS_MASK;

//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
FTM0_MODE &= ~FTM_MODE_FTMEN_MASK; 

//Set Edge Aligned PWM
FTM0_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;  

//QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)
//FTM0_SC = 0x16; //Center Aligned PWM Select = 0, sets FTM Counter to operate in up counting mode, 
//it is field 5 of FTMx_SC (status control) - also setting the pre-scale bits here


/* For proper Servo operation set period to:  50 ms, pulse width to 25ms 
* diagram of FTM Module is on page 899
* 
* period on chip determined by MOD-CNTIN +0x0001 
* pulse width determined by (CnV-CNTIN)  (good descriptions in ref manual on page 956)
* 
* Peripheral bus clock -> 48Mhz  (set up in clock.h) and described in manual on (pg 963)  
* 
* 16 bit counter has 65,536 counts.   
* Set pre-scaler to desired value to have correct clock period.      
*  
* The value of the prescaler is selected by the PS[2:0] bits.  (FTMx_SC field bits 0-2 are Prescale bits - 
* set above in FTM_SC Setting) 
*  001 Divide by 2
*  010 Divide by 4
*  011 Divide by 8
*  100 Divide by 16
*  101 Divide by 32
*  110 Divide by 64 - 
*  111 Divide by 128
*/
//   Also need to setup the FTM2C0SC channel control register  - Page 897   section 37.3.6
FTM0_CNT = 0x0; //FTM Counter Value - (initialize the CNT before writing to MOD)  (16 bit available - bits 0-15 are count)
FTM0_MOD = FTM0_MOD_VALUE; //Set the Modulo resister (16 bit available - bits 0-15), Mod is set to 24000
FTM0_CNTIN = 0; //Set the Counter Initial Value to 0   (pg 915)

//change MSnB = 1


FTM0_C0SC |= FTM_CnSC_ELSB_MASK;
FTM0_C0SC &= ~FTM_CnSC_ELSA_MASK;
FTM0_C0SC |= FTM_CnSC_MSB_MASK;
FTM0_C0V = FTM0_MOD_VALUE/2; //Set the Channel n Value to  (16 bit available - bits 0-15)

//Set the complimentary pinout
FTM0_C1SC |= FTM_CnSC_ELSB_MASK;
FTM0_C1SC &= ~FTM_CnSC_ELSA_MASK;
FTM0_C1SC |= FTM_CnSC_MSB_MASK;
FTM0_C1V = FTM0_MOD_VALUE/2;

FTM0_C2SC |= FTM_CnSC_ELSB_MASK;
FTM0_C2SC &= ~FTM_CnSC_ELSA_MASK;
FTM0_C2SC |= FTM_CnSC_MSB_MASK;
FTM0_C2V = FTM0_MOD_VALUE/2; //Set the Channel n Value to  (16 bit available - bits 0-15)

//Set the complimentary pinout
FTM0_C3SC |= FTM_CnSC_ELSB_MASK;
FTM0_C3SC &= ~FTM_CnSC_ELSA_MASK;
FTM0_C3SC |= FTM_CnSC_MSB_MASK;
FTM0_C3V = FTM0_MOD_VALUE/2;

FTM0_POL |= FTM_POL_POL1_MASK | FTM_POL_POL3_MASK;

TFC_SetMotorPWM(0.0 ,0.0);

FTM0_SC = FTM_SC_PS(0) | FTM_SC_CLKS(1);  

}

void TFC_SetMotorPWM(float MotorA , float MotorB )
{
	FTM0_C0V =(int)((MotorA + 1.0) *((float)FTM0_MOD_VALUE/2.0));
	FTM0_C1V =(int)((MotorA + 1.0) *((float)FTM0_MOD_VALUE/2.0));
	FTM0_C2V =(int)((-1*MotorB + 1.0) *((float)FTM0_MOD_VALUE/2.0));
	FTM0_C3V =(int)((-1*MotorB + 1.0) *((float)FTM0_MOD_VALUE/2.0));
		
}


