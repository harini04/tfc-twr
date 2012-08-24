/*
 * TFC_BoardSupport.h
 *
 *  Created on: Apr 13, 2012
 *      Author: emh203
 */
#include <stdint.h>

#ifndef TFC_BOARDSUPPORT_H_
#define TFC_BOARDSUPPORT_H_


//I/O on Port C
#define TFC_HBRIDGE_A_EN_LOC		(uint32_t)(1<<0)
#define TFC_HBRIDGE_A_FAULT_LOC     (uint32_t)(1<<6)

#define TFC_HBRIDGE_B_EN_LOC		(uint32_t)(1<<5)
#define TFC_HBRIDGE_B_FAULT_LOC     (uint32_t)(1<<7)

#define TFC_HBRIDGE_A_ENABLE		GPIOC_PSOR = TFC_HBRIDGE_A_EN_LOC	
#define TFC_HBRIDGE_A_DISABLE		GPIOC_PCOR = TFC_HBRIDGE_A_EN_LOC	

#define TFC_HBRIDGE_B_ENABLE		GPIOC_PSOR = TFC_HBRIDGE_B_EN_LOC	
#define TFC_HBRIDGE_B_DISABLE		GPIOC_PCOR = TFC_HBRIDGE_B_EN_LOC	

#define TFC_DIP_SWITCH0_LOC			((uint32_t)(1<<8))
#define TFC_DIP_SWITCH1_LOC			((uint32_t)(1<<9))
#define TFC_DIP_SWITCH2_LOC			((uint32_t)(1<<12))
#define TFC_DIP_SWITCH3_LOC			((uint32_t)(1<<13))


#define TFC_PUSH_BUTT0N0_LOC		((uint32_t)(1<<4))
#define TFC_PUSH_BUTT0N1_LOC		 ((uint32_t)(1<<5))	

//I/O on Port D
#define TFC_BAT_LED0_LOC			((uint32_t)(1<<0))
#define TFC_BAT_LED1_LOC			((uint32_t)(1<<1))
#define TFC_BAT_LED2_LOC			((uint32_t)(1<<2))
#define TFC_BAT_LED3_LOC			((uint32_t)(1<<3))


#define TFC_BAT_LED0_ON				GPIOD_PSOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_ON				GPIOD_PSOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_ON				GPIOD_PSOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_ON				GPIOD_PSOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_OFF			GPIOD_PCOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_OFF			GPIOD_PCOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_OFF			GPIOD_PCOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_OFF			GPIOD_PCOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_TOGGLE			GPIOD_PTOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_TOGGLE			GPIOD_PTOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_TOGGLE			GPIOD_PTOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_TOGGLE			GPIOD_PTOR = TFC_BAT_LED3_LOC


#define TFC_PUSH_BUTTON_0_PRESSED	((GPIOD_PDIR&TFC_PUSH_BUTT0N0_LOC)>0)
#define TFC_PUSH_BUTTON_1_PRESSED	((GPIOD_PDIR&TFC_PUSH_BUTT0N1_LOC)>0)

void    TFC_InitGPIO();
void    TFC_SetBatteryLED_Level(uint8_t BattLevel);
uint8_t TFC_GetDIP_Switch();


#endif /* TFC_BOARDSUPPORT_H_ */
