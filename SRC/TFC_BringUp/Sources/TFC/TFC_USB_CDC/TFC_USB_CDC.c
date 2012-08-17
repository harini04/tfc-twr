#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include "usb_cdc.h"        /* USB CDC Class Header File */
#include "virtual_com.h"    /* Virtual COM Application Header File */

#include "TFC\TFC_USB_CDC.h"


//This code is based up on the CDC example from the USB Stack V4.0
//Look in TFC_USB_CDC/sources/app/virtual_com.c for implementation
//Where possible,  the TFC calls are a simple wrapper around existing functions in the example

