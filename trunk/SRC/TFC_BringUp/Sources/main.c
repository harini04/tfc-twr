#include <stdio.h>
#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"

int main(void){
	
	int c = 0;
	uint8_t t;
	uint16_t i,j;
 
    TFC_Init();
		
	for(;;)
	{	
		
		//TFC_Task must be called in your main loop.  This keeps certain processing happy (I.E. USB)
		TFC_Task();

		//This Demo program will look at the middle 2 switch to select one of 4 demo modes.
		//Let's look at the middle 2 switches
		switch((TFC_GetDIP_Switch()>>1)&0x03)
		{
		default:
		case 0 :
			//Demo mode 0 just tests the switches and LED's
			if(TFC_PUSH_BUTTON_0_PRESSED)
				TFC_BAT_LED0_ON;
			else
				TFC_BAT_LED0_OFF;
			
			if(TFC_PUSH_BUTTON_1_PRESSED)
				TFC_BAT_LED3_ON;
			else
				TFC_BAT_LED3_OFF;
			
			break;
		case 1 :
			//Demo mode 1 will just moce the servos with the on-board potentiometers
			if(TFC_Ticker[0]>=20)
			{
				TFC_Ticker[0] = 0; //reset the Ticker
				//Every 20 mSeconds, update the Servos
				TFC_SetServo(0,TFC_ReadPot0());
				TFC_SetServo(1,TFC_ReadPot1());
			}
			//Let's put a pattern on the LEDs
			if(TFC_Ticker[1] >= 125)
			{
				TFC_Ticker[1] = 0;
				t++;
				if(t>4)
				{
					t=0;
				}			
				TFC_SetBatteryLED_Level(t);
			}
			
			break;
			
		case 2 :
			
			//Demo Mode 2 will use the Pots to make the motors move
			
			TFC_SetMotorPWM(TFC_ReadPot0(),TFC_ReadPot1());
					
			//Let's put a pattern on the LEDs
			if(TFC_Ticker[1] >= 125)
				{
					TFC_Ticker[1] = 0;
						t++;
						if(t>4)
						{
							t=0;
						}			
					TFC_SetBatteryLED_Level(t);
			}
			break;
		
		case 3 :
		
			//Demo Mode 3 will be in Freescale Garage Mode.  It will beam data from the Camera to the 
			//Labview Application
			
		#ifdef TFC_USE_LINESCAN_CAMERA
			
			if(TFC_Ticker[0]>99 && LineScanImageReady==1)
				{
				 TFC_Ticker[0] = 0;
				 LineScanImageReady=0;
				 TERMINAL_PRINTF("\r\n");
				 TERMINAL_PRINTF("L:");
				 
				 	if(t==0)
				 		t=3;
				 	else
				 		t--;
				 	
				 TFC_SetBatteryLED_Level(t);
				
				 for(i=0;i<128;i++)
						{
					 	 	 	 TERMINAL_PRINTF("%X,",LineScanImage0[i]);
						}
						for(i=0;i<128;i++)
						{
								 TERMINAL_PRINTF("%X,",LineScanImage1[i]);
						}										
						TERMINAL_PRINTF("\r\n");
				}
				
			
		#endif
			
		#ifdef TFC_USE_NTSC_CAMERA
			
			if(TFC_Ticker[0]>400 )
			{
				TFC_Ticker[0] = 0;
				
				while(TFC_VSyncFlag == 0)
				{
					TFC_Task();
				}
				TFC_VSyncFlag = 0;
				while(TFC_VSyncFlag == 0)
				{
					TFC_Task();
				}
				 Qprintf(&TFC_TWR_UART0_OUTGOING_QUEUE,"V:");
				
	
				 for(i=0;i<TFC_HORIZONTAL_PIXELS;i++)
				 {
				  for(j=0;j<TFC_HORIZONTAL_PIXELS;j++)
					{
					  	  ByteEnqueue(&USB_OUTGOING_TO_PC_QUEUE,0x20 + (TFC_NTSC_IMAGE[4*i][j]>>3));
					}
				 }
				  TERMINAL_PRINTF("\r\n");
									 		
			}
		#endif
			break;
		}
	}
	
	return 0;
}
