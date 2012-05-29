/*
 * TFC_Config.h
 *
 *  Created on: May 12, 2012
 *      Author: EHUGHES
 */

#ifndef TFC_CONFIG_H_
#define TFC_CONFIG_H_

#define PCB_REV				A

//A TFC Ticker is a variable that will increment every 1mS in the Systick interrupt routine
//you can use it to for general purpose timing, scheduling events, etc.  The TFC_Ticker variable
//is just an array of 32-bit integers, use the Macro below to set how many tickers you need

#define NUM_TFC_TICKERS			4

//At least one of these need to be defined!
#define TFC_USE_LINESCAN_CAMERA
//#define TFC_USE_NTSC_CAMERA

//This is what the exposure time for the Linescan will be set to out of bootup
#define TFC_DEFAULT_LINESCAN_EXPOSURE_TIME_uS	20000


#define TFC_MOTOR_SWITCHING_FREQUENCY	((float)(4000.0))


#define TFC_ENABLE_TWR_UART0
#define TFC_ENABLE_TWR_UART1


#define TFC_UART0_BAUD		115200	//This actually maps to UART4 on the chip.  but goes to UART0 on the tower card
#define TFC_UART1_BAUD		115200	//This actually maps to UART3 on the chip.  but goes to UART1 on the tower card


#define TFC_TWR_UART0_OUTGOING_QUEUE_SIZE	16384
#define TFC_TWR_UART0_INCOMING_QUEUE_SIZE	256
#define TFC_TWR_UART1_OUTGOING_QUEUE_SIZE	16
#define TFC_TWR_UART1_INCOMING_QUEUE_SIZE	16


#endif /* TFC_CONFIG_H_ */
