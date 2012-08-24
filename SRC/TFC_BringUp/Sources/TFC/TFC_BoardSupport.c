#include "TFC\TFC.h"


//set I/O for H-BRIDGE enables, switches and LEDs
void TFC_InitGPIO()
{
	//enable Clocks to all ports
	
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK;

	//Setup Pins as GPIO
	PORTC_PCR0 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR6 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR5 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR7 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR8 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR9 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR12 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTC_PCR13 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   

	PORTD_PCR0 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTD_PCR1 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTD_PCR2 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTD_PCR3 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	
	PORTD_PCR4 = PORT_PCR_MUX(1);   
	PORTD_PCR5 = PORT_PCR_MUX(1);
	
	//Setup the output pins
    GPIOC_PDDR =  TFC_HBRIDGE_A_EN_LOC	| TFC_HBRIDGE_B_EN_LOC;
    GPIOD_PDDR =  TFC_BAT_LED0_LOC	| TFC_BAT_LED1_LOC | TFC_BAT_LED2_LOC | TFC_BAT_LED3_LOC;
}


void TFC_SetBatteryLED_Level(uint8_t BattLevel)
{
	switch(BattLevel)
	{
		default:
		case 0:
			GPIOD_PCOR = 0xF;
		break;
	
		case 1:
			GPIOD_PSOR = 0x01;
			GPIOD_PCOR = (~0x01)&0xf;
		break;
		
		case 2:
			GPIOD_PSOR = 0x03;
			GPIOD_PCOR = (~0x03)&0xf;
		break;
		
		case 3:
			GPIOD_PSOR = 0x07;
			GPIOD_PCOR = (~0x07)&0xf;
		break;
		
		case 4:
			GPIOD_PSOR = 0x0F;
			GPIOD_PCOR = 0;
		break;
		
	}
}


uint8_t TFC_GetDIP_Switch()
{
	uint8_t DIP_Val=0;
	
	if(GPIOC_PDIR&TFC_DIP_SWITCH0_LOC)
			DIP_Val|=0x01;
	if(GPIOC_PDIR&TFC_DIP_SWITCH1_LOC)
			DIP_Val|=0x02;
	if(GPIOC_PDIR&TFC_DIP_SWITCH2_LOC)
			DIP_Val|=0x04;
	if(GPIOC_PDIR&TFC_DIP_SWITCH3_LOC)
			DIP_Val|=0x08;
	
	return DIP_Val;
}
