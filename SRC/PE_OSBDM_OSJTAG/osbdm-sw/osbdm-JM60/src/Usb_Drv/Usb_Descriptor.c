/*************************************************************************
 * DISCLAIMER *
 * Services performed by FREESCALE in this matter are performed          *
 * AS IS and without any warranty. CUSTOMER retains the final decision   *
 * relative to the total design and functionality of the end product.    *
 * FREESCALE neither guarantees nor will be held liable by CUSTOMER      *
 * for the success of this project. FREESCALE disclaims all warranties,  *
 * express, implied or statutory including, but not limited to,          *
 * implied warranty of merchantability or fitness for a particular       *
 * purpose on any hardware, software ore advise supplied to the project  *
 * by FREESCALE, and or any product resulting from FREESCALE services.   *
 * In no event shall FREESCALE be liable for incidental or consequential *
 * damages arising out of this agreement. CUSTOMER agrees to hold        *
 * FREESCALE harmless against any and all claims demands or actions      *
 * by anyone on account of any damage, or injury, whether commercial,    *
 * contractual, or tortuous, rising directly or indirectly as a result   *
 * of the advise or assistance supplied CUSTOMER in connection with      *
 * product, services or goods supplied under this Agreement.             *
 *************************************************************************/
/******************************************************************************
 * Copyright (c) 2007, Freescale Semiconductor
 *
 * File name   : Usb_Descriptor.c
 * Project name: JM60 Evaluation code
 *
 * Description : This software evaluates JM60 USB module 
 * History     :
 * 04/01/2007  : Initial Development
 * 03/08/2011  : Modified by P&E Microcomputer Systems to have
 *                 (A) Serial Number Support (if programmed into memory)
 *                 (B) Multifunction Device adding Virtual Serial Port
 *               http://www.pemicro.com/osbdm
 *****************************************************************************/
#include "Usb_Descriptor.h"

const USB_DEV_DSC Device_Dsc_No_Serial_Number =
{    
	sizeof(USB_DEV_DSC),		// bLength - Size of this descriptor in bytes 
	DSC_DEV,						// bDescriptorType - DEVICE descriptor type 
	0x0002,						// bcdUSB - USB Spec Release Number in BCD format 
	0,							// bDeviceClass - Class Code, Vendor Specific 
	0,							// bDeviceSubClass - Subclass code 
	0,      				// bDeviceProtocol - Protocol code, Vendor Specific        
	EP0_BUFF_SIZE,				// bMaxPacketSize - Max packet size for EP0,  
	0xA215,						// idVendor - (15A2) Vendor ID: Freescale, little-endian for USB 
//	0x4200,						// idProduct - (0042) Product ID:	OpenSource BDM, little-endian for USB  
	0x5800,						// idProduct - (0058) Product ID:	OpenSource BDM, NEW PID, Firmware v30
	0x0001,						// bcdProduct - Device release number in BCD format 
	0x01,							// iManufacturer - Manufacturer string index 
	0x02,							// iProduct - Product string index 
	0x00,							// iSerialNumber - Device serial number string index 
	0x01							// bNumConfigurations - Number of possible configurations 
};

const USB_DEV_DSC Device_Dsc_With_Serial_Number =
{    
	sizeof(USB_DEV_DSC),		// bLength - Size of this descriptor in bytes 
	DSC_DEV,						// bDescriptorType - DEVICE descriptor type 
	0x0002,						// bcdUSB - USB Spec Release Number in BCD format 
	0,							// bDeviceClass - Class Code, Vendor Specific 
	0,							// bDeviceSubClass - Subclass code                 
	0,      				// bDeviceProtocol - Protocol code, Vendor Specific 
	EP0_BUFF_SIZE,				// bMaxPacketSize - Max packet size for EP0,  
	0xA215,						// idVendor - (15A2) Vendor ID: Freescale, little-endian for USB 
//	0x4200,						// idProduct - (0042) Product ID:	OpenSource BDM, little-endian for USB   
	0x5800,						// idProduct - (0058) Product ID:	OpenSource BDM, NEW PID
	0x0001,						// bcdProduct - Device release number in BCD format 
	0x01,							// iManufacturer - Manufacturer string index 
	0x02,							// iProduct - Product string index 
	0x04,							// iSerialNumber - Device serial number string index 
	0x01							// bNumConfigurations - Number of possible configurations 
};


 const USB_CFG  Cfg_01=
 {
	// CONFIGURATION DESCRIPTOR
	{
		sizeof(USB_CFG_DSC),			// bLength - Size of this descriptor in bytes
		DSC_CFG,							// bDescriptorType - CONFIGURATION descriptor type
		(word) ((sizeof(USB_CFG)<<8) | (sizeof(USB_CFG)>>8)),	
											// wTotalLenght - total length of data for this cfg
		2,									// bNumInterfaces - Number of interfaces in this cfg
		1,									// bConfigurationValue - index value of this configuration
		0,									// iConfiguration - configuration string index
		_DEFAULT|_REMOTEWAKEUP,		// bmAttributes - attributes, see Usb_Config.h
  		220								// bMaxPower - Max power consumption (2X mA)
  	},
	// Interface Descriptor 
	{
		sizeof(USB_INTF_DSC),   // bLength - Size of this descriptor in bytes
		DSC_INTF,               // bDescriptorType - INTERFACE descriptor type
		0,                      // bInterfaceNumber
		0,                      // bAlternateSetting
		2,                      // bNumEndpoints - # of endpoints in this interface
		0xFF,                      // bInterfaceClass
  		0xFF,                      // bInterfaceSubClass
  		0xFF,                      // bInterfaceProtocol
  		2                       // iInterface - index of string descriptor for this intf
  	},

    
//	 Endpoint Descriptors
//	 bLength
//	 |                 bDescriptorType
//	 |                  |      bEndpointAddress
//	 |                  |      |         bmAttributes
//	 |                  |      |         |      wMaxPacketSize
//	 |                  |      |         |      |                     bInterval 
//	 |                  |      |         |      |                     |           
	{sizeof(USB_EP_DSC),DSC_EP,_EP01_OUT,_BULK,(word)(UEP1_SIZE << 8),0},
	{sizeof(USB_EP_DSC),DSC_EP,_EP02_IN,_BULK,(word)(UEP2_SIZE << 8),0},

	{
		sizeof(USB_INTF_DSC),   // bLength - Size of this descriptor in bytes
		DSC_INTF,               // bDescriptorType - INTERFACE descriptor type
		1,                      // bInterfaceNumber
		0,                      // bAlternateSetting
		2,                      // bNumEndpoints - # of endpoints in this interface
		0xFF,                      // bInterfaceClass
  		0xFF,                      // bInterfaceSubClass
  		0xFF,                      // bInterfaceProtocol
  		3                       // iInterface - index of string descriptor for this intf
  	},

    
//	 Endpoint Descriptors
//	 bLength
//	 |                 bDescriptorType
//	 |                  |      bEndpointAddress
//	 |                  |      |         bmAttributes
//	 |                  |      |         |      wMaxPacketSize
//	 |                  |      |         |      |                     bInterval 
//	 |                  |      |         |      |                     |           
	{sizeof(USB_EP_DSC),DSC_EP,_EP03_OUT,_BULK,(word)(UEP3_SIZE << 8),0},
	{sizeof(USB_EP_DSC),DSC_EP,_EP04_IN,_BULK,(word)(UEP4_SIZE << 8),0},


//	{sizeof(USB_EP_DSC),DSC_EP,_EP05_OUT,_BULK,(word)(UEP5_SIZE << 8),00},
//	{sizeof(USB_EP_DSC),DSC_EP,_EP06_IN,_BULK,(word)(UEP6_SIZE << 8),00}
};


struct
{
	byte bLength;
	byte bDscType;
	word string[1];
} const sd000 = {sizeof(sd000),DSC_STR,0x0904};

struct
{
	byte bLength;
	byte bDscType;
	byte string[54];
} const sd001 = {
	sizeof(sd001),DSC_STR,
	{
	'F', 0,
	'r', 0,
	'e', 0,
	'e', 0,
	's', 0,
	'c', 0,
	'a', 0,
	'l', 0,
	'e', 0,
	' ', 0,
	'S', 0,
	'e', 0,
	'm', 0,
	'i', 0,
	'c', 0,
	'o', 0,
	'n', 0,
	'd', 0,
	'u', 0,
	'c', 0,
	't', 0,
	'o', 0,
	'r', 0,
	' ', 0,
	'I', 0,
	'n', 0,
	'c', 0
	}
};
       

struct
{
	byte bLength;
	byte bDscType;
	byte string[14];
} 
  OSSerialNum = {
	sizeof(OSSerialNum),DSC_STR,
	{
	'O', 0,
	'S', 0,
	'0', 0,
	'0', 0,
	'0', 0,
	'0', 0,
	}
}; 


volatile byte _Serial3 @0x0000FFFA;
volatile byte _Serial2 @0x0000FFFB;
volatile byte _Serial1 @0x0000FFFC;
volatile byte _Serial0 @0x0000FFFD;


struct
{
	byte bLength;
	byte bDscType;
	byte string[36];
} 
  const sd002 = {
	sizeof(sd002),DSC_STR,
	{
	'O', 0,
	'S', 0,
	'B', 0,
	'D', 0,
	'M', 0,
	' ', 0,
	'-', 0,
	' ', 0,
	'D', 0,
	'e', 0,
	'b', 0,
	'u', 0,
	'g', 0,
	' ', 0, 
	'P', 0,
	'o', 0,
	'r', 0,
	't', 0,
	}
}; 

struct
{
	byte bLength;
	byte bDscType;
	byte string[54];
} 
  const sd003 = {
	sizeof(sd003),DSC_STR,
	{
	'O', 0,
	'S', 0,
	'B', 0,
	'D', 0,
	'M', 0,
	' ', 0,
	'-', 0,
	' ', 0,
	'V', 0,
	'i', 0,
	'r', 0,
	't', 0,
	'u', 0,
	'a', 0,
	'l', 0,
	' ', 0,
	'S', 0,
	'e', 0,
	'r', 0,
	'i', 0,
	'a', 0,
	'l', 0,
	' ', 0,
	'P', 0,
	'o', 0,
	'r', 0,
	't', 0,
	}
}; 

    
unsigned char* Str_Des[] = 
	{ (unsigned char*)&sd000,(unsigned char*)&sd001,(unsigned char*)&sd002,(unsigned char*)&sd003, (unsigned char*)&OSSerialNum};   

unsigned char* Cfg_Des[] =
	{(unsigned char*)&Cfg_01,(unsigned char*)&Cfg_01 };
    
pFunc Std_Class_Req_Handler[1] = { NULL };


