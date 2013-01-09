/*
 * TFC_NTSC.c
 *
 *  Created on: May 16, 2012
 *      Author: EHUGHES
 */
#include "TFC\TFC.h"

static uint16_t	TmpEvenFieldLines=0;
static uint16_t	TmpOddFieldLines=0;
static uint8_t	CurrentField=0;

uint8_t TFC_NTSC_IMAGE[TFC_NTSC_LINES_TO_CAPTURE][TFC_HORIZONTAL_PIXELS] = {0};

volatile uint8_t TFC_VSyncFlag = 0;

uint16_t CurrentLine = 0;

uint8_t Field=0;



void TFC_InitNTSC()
{

	//Enable CLock to Port B so the Timer can get out.
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
		
	PORTB_PCR10  = PORT_PCR_MUX(1)  | PORT_PCR_IRQC(0x9); //Vertical Sync Digital Interrupts on rising edge 
	PORTB_PCR9	 = PORT_PCR_MUX(1)  | PORT_PCR_IRQC(0x9);  //Horitzontal Sync Interrupts on Rising Edge
	PORTB_PCR17  =	PORT_PCR_MUX(1)  | PORT_PCR_IRQC(0xB); 				//Odd Even Interrupts on both edges

	//setup the DMA
	//Enable Clock to the DMA Mux and the DMA controller
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	

	//Route ADC- to DMA Channel 0;
	DMAMUX_CHCFG0 = DMAMUX_CHCFG_ENBL_MASK | 40;
	
	//Setup the Transfer Descriptor
	DMA_TCD0_SADDR = (volatile unsigned long)(&ADC0_RA);  // Source is the ADC results Register
	DMA_TCD0_SOFF = 0 ;//No Source Offset
	DMA_TCD0_ATTR = 0 ;//No module on Source and Destination Registers.  8-bit transfers from source to Destination
	
	DMA_TCD0_NBYTES_MLNO= 1; //One transfer per request
	
	DMA_TCD0_SLAST = 0; //Do not increment the source address when a transfer is complete
		
	DMA_TCD0_DADDR = (volatile unsigned long)&TFC_NTSC_IMAGE[0][0];
	DMA_TCD0_DOFF = 1; // Increment desination by one byte
	
	
	DMA_TCD0_CITER_ELINKNO = TFC_HORIZONTAL_PIXELS;	//Major Count, this is the number of pixels to transfer
	DMA_TCD0_BITER_ELINKNO = TFC_HORIZONTAL_PIXELS;	//Major Count, this is the number of pixels to transfer
															
	DMA_TCD0_DLASTSGA = 0;
		
	DMA_TCD0_CSR = DMA_CSR_INTMAJOR_MASK; //DMA request is  turn off when major count is complete
	//Enable interrupts on DMA Complete
	DMA_INT |= DMA_INT_INT0_MASK;

	enable_irq(INT_DMA0-16);
	enable_irq(INT_PORTB-16);

}

void DMA_CH0_IRQ()
{
	//Disable DMa channel 0
	DMA_ERQ &= ~DMA_ERQ_ERQ0_MASK;	
	//Clear the Interrupt Request
	DMA_CINT = 0 ;//
}

void PortB_IRQ()
{
	uint8_t * e;
	
	if(PORTB_PCR10 & PORT_PCR_ISF_MASK) //Vertical Sync
	{
		PORTB_PCR10 |= PORT_PCR_ISF_MASK;
		Field++;
		CurrentLine = 0;
		TFC_VSyncFlag = 1;
		/*Need to implement a ping pong type buffer with DMA to transfer image.  There are some odd
		 * lines showing up in the labiew display. 
		 */
		
	}
	if(PORTB_PCR9 & PORT_PCR_ISF_MASK) //Horizontal Sync
		{
			if(Field&0x01)
			{
		     PORTB_PCR9 |= PORT_PCR_ISF_MASK;
			
		     DMA_TCD0_DADDR = (uint32_t)(&TFC_NTSC_IMAGE[CurrentLine][0]);
			 CurrentLine++;
				//Restart ADC
		     ADC0_SC1A  = 12;
				//Enable DMA channel 0
			 DMA_ERQ |= DMA_ERQ_ERQ0_MASK;	
			}
		}
	  if(PORTB_PCR17 & PORT_PCR_ISF_MASK) //Even/Odd
		{
			PORTB_PCR17 |= PORT_PCR_ISF_MASK;
		}
}

