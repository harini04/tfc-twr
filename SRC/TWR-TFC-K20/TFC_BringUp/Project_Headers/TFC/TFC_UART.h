/*
 * TFC_UART.h
 *
 *  Created on: May 19, 2012
 *      Author: EHUGHES
 */

#ifndef TFC_UART_H_
#define TFC_UART_H_

void TFC_InitUARTs();

void UART3_ISR();
void UART4_ISR();

void TFC_UART_Process();

extern ByteQueue TFC_TWR_UART0_OUTGOING_QUEUE;
extern ByteQueue TFC_TWR_UART0_INCOMING_QUEUE;
extern ByteQueue TFC_TWR_UART1_OUTGOING_QUEUE;
extern ByteQueue TFC_TWR_UART1_INCOMING_QUEUE;

#endif /* TFC_UART_H_ */
