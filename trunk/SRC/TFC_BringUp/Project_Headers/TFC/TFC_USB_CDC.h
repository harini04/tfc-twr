#include "TFC\TFC_Queue.h"

#ifndef TFC_USB_CDC_H_
#define TFC_USB_CDC_H_

extern void USB_ISR(void);

#define USB_CDC_QUEUE_SIZE_OUTGOING		4096
#define USB_CDC_QUEUE_SIZE_INCOMING	    4096

void TFC_InitUSB_VirtualCOM_Port();
void TFC_USB_VirtualCOM_Process();

extern ByteQueue USB_OUTGOING_TO_PC_QUEUE;
extern ByteQueue USB_INCOMING_FROM_PC_QUEUE;


extern uint8_t USB_OUTGOING_TO_PC_QUEUE_Storage[USB_CDC_QUEUE_SIZE_OUTGOING];
extern uint8_t USB_INCOMING_FROM_PC_QUEUE_Storage[USB_CDC_QUEUE_SIZE_INCOMING];

#endif /* TFC_USB_CDC_H_ */
