/*
 * TFC_LineScanCamera.h
 *
 *  Created on: May 8, 2012
 *      Author: ehughes
 */

#ifndef TFC_LINESCANCAMERA_H_
#define TFC_LINESCANCAMERA_H_


void TFC_InitLineScanCamera();
void TFC_LineScanImageCamera();

void TFC_SetLineScanExposureTime(uint32_t  TimeIn_uS);


#define TAOS_CLK_HIGH  GPIOE_PSOR = (1<<4)  
#define TAOS_CLK_LOW   GPIOE_PCOR = (1<<4)  
#define TAOS_SI_HIGH   GPIOE_PSOR = (1<<5)
#define TAOS_SI_LOW    GPIOE_PCOR =	(1<<5)
#define GET_CAMERA0_ANALOG_OUT	Read_ADC1(6)			
#define GET_CAMERA1_ANALOG_OUT	Read_ADC1(7)			


extern volatile uint8_t  *LineScanImage0WorkingBuffer;
extern volatile uint8_t  *LineScanImage1WorkingBuffer;
extern volatile uint8_t  *LineScanImage0;
extern volatile uint8_t  *LineScanImage1;
extern volatile uint8_t  LineScanImage0Buffer[2][128];
extern volatile uint8_t  LineScanImage1Buffer[2][128];
extern volatile uint8_t  LineScanWorkingBuffer;
extern volatile uint8_t  LineScanImageReady;

#endif /* TFC_LINESCANCAMERA_H_ */
