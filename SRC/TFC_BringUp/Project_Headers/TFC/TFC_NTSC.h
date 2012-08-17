/*
 * TFC_NTSC.h
 *
 *  Created on: May 16, 2012
 *      Author: EHUGHES
 */

#ifndef TFC_NTSC_H_
#define TFC_NTSC_H_

void TFC_InitNTSC();
void PortB_IRQ();
void DMA_CH0_IRQ();

extern uint16_t	EvenFieldLines;
extern uint16_t	OddFieldLines;

#define TFC_HORIZONTAL_TIME			(4.7 + 52.6)		//This includes the time from Horizontal sync rising Edge to end of video
#define TFC_NTSC_ADC_SAMPLE_TIME 	(0.9)
#define TFC_HORIZONTAL_PIXELS 		 ((uint16_t)((TFC_HORIZONTAL_TIME/TFC_NTSC_ADC_SAMPLE_TIME) + 2))//(TFC_HORIZONTAL_TIME/TFC_NTSC_ADC_SAMPLE_TIME)			

#define TFC_NTSC_LINES_TO_CAPTURE    320  //We are just going to capture the even field

#define TFC_NTSC_LINES_TO_DISPLAY    (TFC_NTSC_LINES_TO_CAPTURE/TFC_HORIZONTAL_PIXELS)
 
#define TFC_NTSC_IMAGE_SIZE_IN_BYTES  (TFC_NTSC_LINES_TO_CAPTURE*TFC_HORIZONTAL_PIXELS)


extern uint8_t TFC_NTSC_IMAGE[TFC_NTSC_LINES_TO_CAPTURE][TFC_HORIZONTAL_PIXELS];

extern volatile uint8_t TFC_VSyncFlag;
#endif /* TFC_NTSC_H_ */
