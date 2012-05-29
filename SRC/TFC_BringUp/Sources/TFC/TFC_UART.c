#include "TFC\TFC.h"

//Note:   These are freescale supplied examples for init.  They show a basic blocking serial read/write.
//we use there nice setup function.   The InitUart only sets up the Uart hardware.  You still have to enable it on the pin
//(pin control mux) and make sure its clock is enabled.

void InitUart (UART_MemMapPtr uartch, uint32_t sysclk, uint32_t baud);

ByteQueue TFC_TWR_UART0_OUTGOING_QUEUE;
ByteQueue TFC_TWR_UART0_INCOMING_QUEUE;
ByteQueue TFC_TWR_UART1_OUTGOING_QUEUE;
ByteQueue TFC_TWR_UART1_INCOMING_QUEUE;

uint8_t TFC_TWR_UART0_OUTGOING_QUEUE_Storage[TFC_TWR_UART0_OUTGOING_QUEUE_SIZE];
uint8_t TFC_TWR_UART0_INCOMING_QUEUE_Storage[TFC_TWR_UART0_INCOMING_QUEUE_SIZE];

uint8_t TFC_TWR_UART1_OUTGOING_QUEUE_Storage[TFC_TWR_UART1_OUTGOING_QUEUE_SIZE];
uint8_t TFC_TWR_UART1_INCOMING_QUEUE_Storage[TFC_TWR_UART1_INCOMING_QUEUE_SIZE];


void TFC_InitUARTs()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	InitByteQueue(&TFC_TWR_UART0_OUTGOING_QUEUE,TFC_TWR_UART0_OUTGOING_QUEUE_SIZE,TFC_TWR_UART0_OUTGOING_QUEUE_Storage);
	InitByteQueue(&TFC_TWR_UART0_INCOMING_QUEUE,TFC_TWR_UART0_INCOMING_QUEUE_SIZE,TFC_TWR_UART0_INCOMING_QUEUE_Storage);
	InitByteQueue(&TFC_TWR_UART1_OUTGOING_QUEUE,TFC_TWR_UART1_OUTGOING_QUEUE_SIZE,TFC_TWR_UART1_OUTGOING_QUEUE_Storage);
	InitByteQueue(&TFC_TWR_UART1_INCOMING_QUEUE,TFC_TWR_UART1_INCOMING_QUEUE_SIZE,TFC_TWR_UART1_INCOMING_QUEUE_Storage);
	
	PORTC_PCR14 = PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK;   
	PORTC_PCR15 = PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK;  
	PORTC_PCR16 = PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK;  
	PORTC_PCR17 = PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK;  
	
	InitUart (UART3_BASE_PTR,PERIPHERAL_BUS_CLOCK, TFC_UART0_BAUD);
	InitUart (UART4_BASE_PTR,PERIPHERAL_BUS_CLOCK, TFC_UART1_BAUD);
	
	UART3_C2 |= UART_C2_RIE_MASK; //Enable Reciever Interrupts
	UART4_C2 |= UART_C2_RIE_MASK; //Enable Reciever Interrupts
	
	//enable_irq(INT_UART3_RX_TX-16);
	enable_irq(INT_UART4_RX_TX-16);
		
}

void TFC_UART_Process()
{
	if(BytesInQueue(&TFC_TWR_UART0_OUTGOING_QUEUE)>0 && (UART4_S1 & UART_S1_TDRE_MASK))
			UART4_C2 |= UART_C2_TIE_MASK; //Enable Transmitter Interrupts
	if(BytesInQueue(&TFC_TWR_UART1_OUTGOING_QUEUE)>0 && (UART3_S1 & UART_S1_TDRE_MASK))
			UART3_C2 |= UART_C2_TIE_MASK; //Enable Transmitter Interrupts
}

void UART3_ISR()
{
	uint8_t Temp;
			
	if(UART3_S1 & UART_S1_RDRF_MASK)
	{
		ByteEnqueue(&TFC_TWR_UART1_INCOMING_QUEUE,UART3_D);
	}
	if(UART3_S1 & UART_S1_TDRE_MASK)
	{
		if(BytesInQueue(&TFC_TWR_UART1_OUTGOING_QUEUE)>0)
		{
			ByteDequeue(&TFC_TWR_UART1_OUTGOING_QUEUE,&Temp);
			UART3_D = Temp;
		}
		else
		{
			//if there is nothing left in the queue then disable interrupts
			UART3_C2 &= ~UART_C2_TIE_MASK; //Disable the  Interrupts
		}
	}
}

void UART4_ISR()
{
	uint8_t Temp;
		
	if(UART4_S1 & UART_S1_RDRF_MASK)
	{
		ByteEnqueue(&TFC_TWR_UART0_INCOMING_QUEUE,UART4_D);
	}
	if(UART4_S1 & UART_S1_TDRE_MASK)
	{
		if(BytesInQueue(&TFC_TWR_UART0_OUTGOING_QUEUE)>0)
		{
			ByteDequeue(&TFC_TWR_UART0_OUTGOING_QUEUE,&Temp);
			UART4_D = Temp;
		}
		else
		{
			//if there is nothing left in the queue then disable interrupts
			UART4_C2 &= ~UART_C2_TIE_MASK; //Disable the  Interrupts
		}
	}
}

void InitUart (UART_MemMapPtr uartch, uint32_t sysclk, uint32_t baud)
{
    uint16_t sbr, brfa;
    uint8_t temp;
    
	/* Enable the clock to the selected UART */    
    if(uartch == UART0_BASE_PTR)
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
    else
    	if (uartch == UART1_BASE_PTR)
			SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
    	else
    		if (uartch == UART2_BASE_PTR)
    			SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
    		else
    			if(uartch == UART3_BASE_PTR)
    				SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
    			else
    				if(uartch == UART4_BASE_PTR)
    					SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
    				else
    					SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;
                                
    /* Make sure that the transmitter and receiver are disabled while we 
     * change settings.
     */
   
    UART_C2_REG(uartch) &= ~(UART_C2_TE_MASK
				| UART_C2_RE_MASK );

    /* Configure the UART for 8-bit mode, no parity */
    UART_C1_REG(uartch) = 0;	/* We need all default settings, so entire register is cleared */
    
    /* Calculate baud settings */
    sbr = (uint32_t)((sysclk)/(baud * 16));
        
    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(uartch) & ~(UART_BDH_SBR(0x1F));
    
    UART_BDH_REG(uartch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(uartch) = (uint8_t)(sbr & UART_BDL_SBR_MASK);
    
    /* Determine if a fractional divider is needed to get closer to the baud rate */
    brfa = (((sysclk*32000)/(baud * 16)) - (sbr * 32));
    
    /* Save off the current value of the UARTx_C4 register except for the BRFA field */
    temp = UART_C4_REG(uartch) & ~(UART_C4_BRFA(0x1F));
    
    UART_C4_REG(uartch) = temp |  UART_C4_BRFA(brfa);    

    /* Enable receiver and transmitter */
	UART_C2_REG(uartch) |= (UART_C2_TE_MASK
				| UART_C2_RE_MASK );
}

/********************************************************************/
/*
 * Wait for space in the UART Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  ch			 character to send
 */ 
void uart_putchar (UART_MemMapPtr channel, uint8_t ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));
    
    /* Send the character */
    UART_D_REG(channel) = (uint8_t)ch;
 }
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      UART channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present (UART_MemMapPtr channel)
{
    return (UART_S1_REG(channel) & UART_S1_RDRF_MASK);
}
/********************************************************************/

/********************************************************************/
/*
 * Wait for a character to be received on the specified UART
 *
 * Parameters:
 *  channel      UART channel to read from
 *
 * Return Values:
 *  the received character
 */
char uart_getchar (UART_MemMapPtr channel)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));
    
    /* Return the 8-bit data from the receiver */
    return UART_D_REG(channel);
}
