#include "TFC\TFC_Config.h"
#include "TFC\TFC_UART.h"

#ifndef TFC_TERMINAL_H_
#define TFC_TERMINAL_H_

void TFC_InitTerminal();
void TFC_ProcessTerminal();


#if defined(TERMINAL_USE_TWR_UART0)

	#define TERMINAL_OUT_QUEUE			TFC_TWR_UART0_OUTGOING_QUEUE
	#define TERMINAL_IN_QUEUE			TFC_TWR_UART0_OUTGOING_QUEUE
	#define TERMINAL_PRINTF(...)   		Qprintf(&TERMINAL_OUT_QUEUE,__VA_ARGS__)  
	#define TERMINAL_PUTC(c)        	ByteEnqueue(&TERMINAL_OUT_QUEUE,c)
	#define TERMINAL_READABLE       	BytesInQueue(&TERMINAL_IN_QUEUE)
	#define TERMINAL_GETC           	ForcedByteDequeue(&TERMINAL_IN_QUEUE)
#elif defined(TERMINAL_USE_USB_CDC)

	#define TERMINAL_OUT_QUEUE			USB_OUTGOING_TO_PC_QUEUE
	#define TERMINAL_IN_QUEUE			USB_INCOMING_FROM_PC_QUEUE
	#define TERMINAL_PRINTF(...) 	  	Qprintf(&TERMINAL_OUT_QUEUE,__VA_ARGS__)  
	#define TERMINAL_PUTC(c)        	ByteEnqueue(&TERMINAL_OUT_QUEUE,c)
	#define TERMINAL_READABLE       	BytesInQueue(&TERMINAL_IN_QUEUE)
	#define TERMINAL_GETC           	ForcedByteDequeue(&TERMINAL_IN_QUEUE)

#else TERMINAL_USE_USB_CDC
	#error "Unsupported Terminal Configuration!"
#endif



#endif /* TFC_TERMINAL_H_ */
