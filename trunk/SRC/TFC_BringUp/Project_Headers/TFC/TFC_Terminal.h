#include "TFC\TFC_Config.h"
#include "TFC\TFC_UART.h"

#ifndef TFC_TERMINAL_H_
#define TFC_TERMINAL_H_

void TFC_InitTerminal();
void TFC_ProcessTerminal();


#ifdef TERMINAL_USE_TWR_UART0

	#define TERMINAL_PRINTF(...)   	Qprintf(&TFC_TWR_UART0_OUTGOING_QUEUE,__VA_ARGS__)  
	#define TERMINAL_PUTC(c)        ByteEnqueue(&TFC_TWR_UART0_OUTGOING_QUEUE,c)
	#define TERMINAL_READABLE       BytesInQueue(&TFC_TWR_UART0_INCOMING_QUEUE)
	#define TERMINAL_GETC           ForcedByteDequeue(&TFC_TWR_UART0_INCOMING_QUEUE)

#else

	#error "Terminal Output not supported"

#endif


#endif /* TFC_TERMINAL_H_ */
