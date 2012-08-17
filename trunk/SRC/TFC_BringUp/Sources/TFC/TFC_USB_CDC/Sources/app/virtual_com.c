/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_com.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief  The file emulates a USB PORT as Loopback Serial Port.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include "usb_cdc.h"        /* USB CDC Class Header File */
#include "virtual_com.h"    /* Virtual COM Application Header File */
#include <stdio.h>
#include "TFC_USB_CDC.h"

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
#include "exceptions.h"
#endif

/* skip the inclusion in dependency state */
#ifndef __NO_SETJMP
	#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void TestApp_Init(void);

/****************************************************************************
 * Global Variables
 ****************************************************************************/
#if HIGH_SPEED_DEVICE
uint_32 g_cdcBuffer[DIC_BULK_OUT_ENDP_PACKET_SIZE>>1];
#endif

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_App_Callback(uint_8 controller_ID,
                        uint_8 event_type, void* val);
static void USB_Notify_Callback(uint_8 controller_ID,
                        uint_8 event_type, void* val);
static void Virtual_Com_App(void);
void TestApp_Init(void);

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif
/* Virtual COM Application start Init Flag */
static volatile boolean start_app = FALSE;
/* Virtual COM Application Carrier Activate Flag */
static volatile boolean start_transactions = FALSE;
/* Receive Buffer */
static uint_8 g_curr_recv_buf[DATA_BUFF_SIZE];
/* Send Buffer */
static uint_8 g_curr_send_buf[DATA_BUFF_SIZE];
/* Receive Data Size */
static uint_8 g_recv_size;
/* Send Data Size */
static uint_8 g_send_size;

uint8_t rts = 1;

ByteQueue USB_OUTGOING_TO_PC_QUEUE;
ByteQueue USB_INCOMING_FROM_PC_QUEUE;
uint8_t USB_OUTGOING_TO_PC_QUEUE_Storage[USB_CDC_QUEUE_SIZE_OUTGOING];
uint8_t USB_INCOMING_FROM_PC_QUEUE_Storage[USB_CDC_QUEUE_SIZE_INCOMING];


#define HOLDING_BUFFER_SIZE	255
uint8_t USB_HoldingBuffer[MAX_QUEUE_ELEMS][HOLDING_BUFFER_SIZE];
uint16_t USB_BufferSize[MAX_QUEUE_ELEMS];
uint8_t CurrentHoldingBuffer;

                       

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
 /******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for the Virtual COM Loopback app
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************
 * This function starts the Virtual COM Loopback application
 *****************************************************************************/

void TFC_InitUSB_VirtualCOM_Port()
{
	CurrentHoldingBuffer = 0;
	
	InitByteQueue(&USB_INCOMING_FROM_PC_QUEUE,USB_CDC_QUEUE_SIZE_INCOMING,&USB_INCOMING_FROM_PC_QUEUE_Storage[0]);
	InitByteQueue(&USB_OUTGOING_TO_PC_QUEUE,USB_CDC_QUEUE_SIZE_OUTGOING,&USB_OUTGOING_TO_PC_QUEUE_Storage[0]);
	TestApp_Init();
}

void TestApp_Init(void)
{
    uint_8   error;

    g_recv_size = 0;
    g_send_size= 0;
    DisableInterrupts;		
    #if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_dis();
    #endif
    /* Initialize the USB interface */
    error = USB_Class_CDC_Init(CONTROLLER_ID,USB_App_Callback,
                                NULL,USB_Notify_Callback, TRUE);
    if(error != USB_OK)
    {
        /* Error initializing USB-CDC Class */
        return;
    }
    EnableInterrupts;
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_en();
    #endif
}


/******************************************************************************
 *
 *   @name        TestApp_Task
 *
 *   @brief       Application task function. It is called from the main loop
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * Application task function. It is called from the main loop
 *****************************************************************************/
void TestApp_Task(void)
{
#if (defined _MC9S08JE128_H) || (defined _MC9S08JM16_H) || (defined _MC9S08JM60_H) || (defined _MC9S08JS16_H) || (defined _MC9S08MM128_H)
	if(USB_PROCESS_PENDING())
	{
		USB_Engine();
	}
#endif
        /* call the periodic task function */
        USB_Class_CDC_Periodic_Task();

       /*check whether enumeration is complete or not */
        if((start_app==TRUE) && (start_transactions==TRUE))
        {
            Virtual_Com_App();
        }
}

/******************************************************************************
 *
 *    @name       Virtual_Com_App
 *
 *    @brief      Implements Loopback COM Port
 *
 *    @param      None
 *
 *    @return     None
 *
 *****************************************************************************
 * Receives data from USB Host and transmits back to the Host
 *****************************************************************************/
static void Virtual_Com_App(void);

void TFC_USB_VirtualCOM_Process()
{
	  /* call the periodic task function */
	        USB_Class_CDC_Periodic_Task();

	       /*check whether enumeration is complete or not */
	        if((start_app==TRUE) && (start_transactions==TRUE))
	        {
	            Virtual_Com_App();
	        }
}

static void Virtual_Com_App(void)
{
    static uint_8 status = 0;
    uint16_t BytesToSend;
    uint16_t i;
                
    /* Loopback Application Code */
    if(g_recv_size)
    {
    	ByteArrayEnqueue(&USB_INCOMING_FROM_PC_QUEUE, g_curr_recv_buf,g_recv_size);
    	g_recv_size = 0;
    }
  
        BytesToSend = BytesInQueue(&USB_OUTGOING_TO_PC_QUEUE);
        
       	if(BytesToSend>0)
			{
       		
				if(BytesToSend<HOLDING_BUFFER_SIZE	)
				{
					for(i=0;i<BytesToSend;i++)
					{
						ByteDequeue(&USB_OUTGOING_TO_PC_QUEUE,&USB_HoldingBuffer[CurrentHoldingBuffer][i]);
					}
					 USB_BufferSize[CurrentHoldingBuffer]  = BytesToSend;
				}
				else
				{
				  for(i=0;i<HOLDING_BUFFER_SIZE;i++)
					{
						ByteDequeue(&USB_OUTGOING_TO_PC_QUEUE,&USB_HoldingBuffer[CurrentHoldingBuffer][i]);
					}
				  USB_BufferSize[CurrentHoldingBuffer] = HOLDING_BUFFER_SIZE;
				}
				  
				status = USB_Class_CDC_Interface_DIC_Send_Data(CONTROLLER_ID,
						&USB_HoldingBuffer[CurrentHoldingBuffer][0], USB_BufferSize[CurrentHoldingBuffer]);
				
				if(status != USB_OK)
				{
					/* Send Data Error Handling Code goes here */
				}
			
				CurrentHoldingBuffer++;
				if(CurrentHoldingBuffer == MAX_QUEUE_ELEMS)
					CurrentHoldingBuffer = 0;
			}
      
   

    return;
}

/******************************************************************************
 *
 *    @name        USB_App_Callback
 *
 *    @brief       This function handles Class callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : Value of the event
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the class layer whenever reset occurs or enum
 * is complete. After the enum is complete this function sets a variable so
 * that the application can start.
 * This function also receives DATA Send and RECEIVED Events
 *****************************************************************************/

static void USB_App_Callback (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event_type,      /* [IN] value of the event */
    void* val               /* [IN] gives the configuration value */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    if(event_type == USB_APP_BUS_RESET)
    {
        start_app=FALSE;
    }
    else if(event_type == USB_APP_ENUM_COMPLETE)
    {    	
#if HIGH_SPEED_DEVICE
    	// prepare for the next receive event
    	USB_Class_CDC_Interface_DIC_Recv_Data(&controller_ID,
    	                                      (uint_8_ptr)g_cdcBuffer, 
    	                                      DIC_BULK_OUT_ENDP_PACKET_SIZE);
#endif
        start_app=TRUE;
    }
    else if((event_type == USB_APP_DATA_RECEIVED)&&
            (start_transactions == TRUE))
    {
        /* Copy Received Data buffer to Application Buffer */
        USB_PACKET_SIZE BytesToBeCopied;
        APP_DATA_STRUCT* dp_rcv = (APP_DATA_STRUCT*)val;
        uint_8 index;
        BytesToBeCopied = (USB_PACKET_SIZE)((dp_rcv->data_size > DATA_BUFF_SIZE) ?
                                      DATA_BUFF_SIZE:dp_rcv->data_size);
        for(index = 0; index<BytesToBeCopied ; index++)
        {
            g_curr_recv_buf[index]= dp_rcv->data_ptr[index];
        }
        g_recv_size = index;
    }
    else if((event_type == USB_APP_SEND_COMPLETE) && (start_transactions == TRUE))
    {
        /* Previous Send is complete. Queue next receive */
#if HIGH_SPEED_DEVICE
    	(void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, g_cdcBuffer, DIC_BULK_OUT_ENDP_PACKET_SIZE);
#else
        (void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, NULL, 0);
#endif
      
    }

    return;
}

/******************************************************************************
 *
 *    @name        USB_Notify_Callback
 *
 *    @brief       This function handles PSTN Sub Class callbacks
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : PSTN Event Type
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function handles USB_APP_CDC_CARRIER_ACTIVATED and
 * USB_APP_CDC_CARRIER_DEACTIVATED PSTN Events
 *****************************************************************************/

static void USB_Notify_Callback (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event_type,      /* [IN] PSTN Event Type */
    void* val               /* [IN] gives the configuration value */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    if(start_app == TRUE)
    {
        if(event_type == USB_APP_CDC_CARRIER_ACTIVATED)
        {
            start_transactions = TRUE;
        }
        else if(event_type == USB_APP_CDC_CARRIER_DEACTIVATED)
        {
            start_transactions = FALSE;
        }
    }
    return;
}

/* EOF */
