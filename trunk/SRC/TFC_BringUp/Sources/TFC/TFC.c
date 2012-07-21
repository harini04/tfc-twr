/*
 * TFC.c
 *
 *  Created on: Apr 13, 2012
 *      Author: emh203
 */

#include "TFC\TFC.h"


void TFC_Init()
{
	TFC_InitClock();
	TFC_InitSysTick();
	
	
	TFC_InitTerminal();
	
	TFC_InitGPIO();
	TFC_InitServos();
	InitADCs();
	TFC_InitMotorPWM();
	TFC_InitUARTs();
	
	#ifdef TFC_USE_LINESCAN_CAMERA
		TFC_InitLineScanCamera();
	#endif
		
	#ifdef TFC_USE_NTSC_CAMERA
		TFC_InitNTSC();
	#endif
		
	TFC_HBRIDGE_A_ENABLE;
	TFC_HBRIDGE_B_ENABLE;
	
	TFC_InitUSB_VirtualCOM_Port();
}

void TFC_Task()
{
	 TFC_USB_VirtualCOM_Process();
	 TFC_UART_Process();
	 TFC_ProcessTerminal();
}