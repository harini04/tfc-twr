#include "TFC\TFC.h"

#if (defined MCU_MK20D7) || (defined MCU_MK40D7)
	#define MCGOUTCLK_72_MHZ
#endif

#if (defined MCU_MK60N512VMD100) || (defined MCU_MK53N512CMD100)
	#define BSP_CLOCK_SRC                   (50000000ul)       	// crystal, oscillator freq.
#else
	#define BSP_CLOCK_SRC                   (8000000ul)       	// crystal, oscillator freq.
#endif
#define BSP_REF_CLOCK_SRC               (2000000ul)       		// must be 2-4MHz

#ifdef MCGOUTCLK_72_MHZ
	#define BSP_CORE_DIV                    (1)
	#define BSP_BUS_DIV                     (2)
	#define BSP_FLEXBUS_DIV                 (2)
	#define BSP_FLASH_DIV                   (3)

	// BSP_CLOCK_MUL from interval 24 - 55
	#define BSP_CLOCK_MUL                   (36)    // 72MHz
#else
	#define BSP_CORE_DIV                    (1)
	#define BSP_BUS_DIV                     (1)
	#define BSP_FLEXBUS_DIV                 (1)
	#define BSP_FLASH_DIV                   (2)

	// BSP_CLOCK_MUL from interval 24 - 55
	#define BSP_CLOCK_MUL                   (24)    // 48MHz
#endif

#define BSP_REF_CLOCK_DIV               (BSP_CLOCK_SRC / BSP_REF_CLOCK_SRC)

#define BSP_CLOCK                       (BSP_REF_CLOCK_SRC * BSP_CLOCK_MUL)
#define BSP_CORE_CLOCK                  (BSP_CLOCK / BSP_CORE_DIV)          // CORE CLK, max 100MHz
#define BSP_SYSTEM_CLOCK                (BSP_CORE_CLOCK)                    // SYSTEM CLK, max 100MHz
#define BSP_BUS_CLOCK                   (BSP_CLOCK / BSP_BUS_DIV)       // max 50MHz
#define BSP_FLEXBUS_CLOCK               (BSP_CLOCK / BSP_FLEXBUS_DIV)
#define BSP_FLASH_CLOCK                 (BSP_CLOCK / BSP_FLASH_DIV)     // max 25MHz

#ifdef MCU_MK70F12
enum usbhs_clock
{
  MCGPLL0,
  MCGPLL1,
  MCGFLL,
  PLL1,
  CLKIN
};

// Constants for use in pll_init
#define NO_OSCINIT 0
#define OSCINIT 1

#define OSC_0 0
#define OSC_1 1

#define LOW_POWER 0
#define HIGH_GAIN 1

#define CANNED_OSC  0
#define CRYSTAL 1

#define PLL_0 0
#define PLL_1 1

#define PLL_ONLY 0
#define MCGOUT 1

#define BLPI 1
#define FBI  2
#define FEI  3
#define FEE  4
#define FBE  5
#define BLPE 6
#define PBE  7
#define PEE  8

// IRC defines
#define SLOW_IRC 0
#define FAST_IRC 1

/*
 * Input Clock Info
 */
#define CLK0_FREQ_HZ        50000000
#define CLK0_TYPE           CANNED_OSC

#define CLK1_FREQ_HZ        12000000
#define CLK1_TYPE           CRYSTAL

/* Select Clock source */
/* USBHS Fractional Divider value for 120MHz input */
/* USBHS Clock = PLL0 x (USBHSFRAC+1) / (USBHSDIV+1)       */
#define USBHS_FRAC    0
#define USBHS_DIV     SIM_CLKDIV2_USBHSDIV(1)
#define USBHS_CLOCK   MCGPLL0


/* USB Fractional Divider value for 120MHz input */
/** USB Clock = PLL0 x (FRAC +1) / (DIV+1)       */
/** USB Clock = 120MHz x (1+1) / (4+1) = 48 MHz    */
#define USB_FRAC    SIM_CLKDIV2_USBFSFRAC_MASK
#define USB_DIV     SIM_CLKDIV2_USBFSDIV(4)


/* Select Clock source */
#define USB_CLOCK   MCGPLL0
//#define USB_CLOCK   MCGPLL1
//#define USB_CLOCK   MCGFLL
//#define USB_CLOCK   PLL1
//#define USB_CLOCK   CLKIN

/* The expected PLL output frequency is:
 * PLL out = (((CLKIN/PRDIV) x VDIV) / 2)
 * where the CLKIN can be either CLK0_FREQ_HZ or CLK1_FREQ_HZ.
 * 
 * For more info on PLL initialization refer to the mcg driver files.
 */

#define PLL0_PRDIV      5
#define PLL0_VDIV       24

#define PLL1_PRDIV      5
#define PLL1_VDIV       30
#endif


void __relocate_code__ TFC_InitClock()
{
// If the internal load capacitors are being used, they should be selected 
// before enabling the oscillator. Application specific. 16pF and 8pF selected
// in this example
  OSC_CR = OSC_CR_SC16P_MASK | OSC_CR_SC8P_MASK;
// Enabling the oscillator for 8 MHz crystal
// RANGE=1, should be set to match the frequency of the crystal being used
// HGO=1, high gain is selected, provides better noise immunity but does draw
// higher current
// EREFS=1, enable the external oscillator
// LP=0, low power mode not selected (not actually part of osc setup)
// IRCS=0, slow internal ref clock selected (not actually part of osc setup)
  MCG_C2 = MCG_C2_RANGE(1) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK;
// Select ext oscillator, reference divider and clear IREFS to start ext osc
// CLKS=2, select the external clock source 
// FRDIV=3, set the FLL ref divider to keep the ref clock in range 
//         (even if FLL is not being used) 8 MHz / 256 = 31.25 kHz         
// IREFS=0, select the external clock 
// IRCLKEN=0, disable IRCLK (can enable it if desired)
// IREFSTEN=0, disable IRC in stop mode (can keep it enabled in stop if desired)
  MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
// wait for oscillator to initialize
  while (!(MCG_S & MCG_S_OSCINIT_MASK)){}  
// wait for Reference clock to switch to external reference 
  while (MCG_S & MCG_S_IREFST_MASK){} 
// Wait for MCGOUT to switch over to the external reference clock 
  while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2){}
// Now configure the PLL and move to PBE mode
// set the PRDIV field to generate a 4MHz reference clock (8MHz /2)
  MCG_C5 = MCG_C5_PRDIV(1); // PRDIV=1 selects a divide by 2
// set the VDIV field to 0, which is x24, giving 4 x 24  = 96 MHz
// the PLLS bit is set to enable the PLL
// the clock monitor is enabled, CME=1 to cause a reset if crystal fails  
// LOLIE can be optionally set to enable the loss of lock interrupt
  
  MCG_C6 = MCG_C6_CME_MASK | MCG_C6_PLLS_MASK;
// wait until the source of the PLLS clock has switched to the PLL  
  while (!(MCG_S & MCG_S_PLLST_MASK)){}
// wait until the PLL has achieved lock
  while (!(MCG_S & MCG_S_LOCK_MASK)){}
// set up the SIM clock dividers BEFORE switching to the PLL to ensure the
// system clock speeds are in spec.
// core = PLL (96MHz), bus = PLL/2 (48MHz), flexbus = PLL/2 (48MHz), flash = PLL/4 (24MHz)  
  SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(1) 
              | SIM_CLKDIV1_OUTDIV3(1) | SIM_CLKDIV1_OUTDIV4(3);
  
// Transition into PEE by setting CLKS to 0
// previous MCG_C1 settings remain the same, just need to set CLKS to 0
  MCG_C1 &= ~MCG_C1_CLKS_MASK;
// Wait for MCGOUT to switch over to the PLL
  while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3){}

        
}



/*****************************************************************************
 * @name     pll_init
 *
 * @brief:   Initialization of the MCU.
 *
 * @param  : None
 *
 * @return : None
 *****************************************************************************
 * It will configure the MCU to disable STOP and COP Modules.
 * It also set the MCG configuration and bus clock frequency.
 ****************************************************************************/
 int pll_init(
#ifdef MCU_MK70F12
	unsigned char init_osc, 
	unsigned char osc_select, 
	int crystal_val, 
	unsigned char hgo_val, 
	unsigned char erefs_val, 
	unsigned char pll_select, 
	signed char prdiv_val, 
	signed char vdiv_val, 
	unsigned char mcgout_select
#endif
		)
{
#ifndef MCU_MK70F12
    /* 
     * First move to FBE mode
     * Enable external oscillator, RANGE=0, HGO=, EREFS=, LP=, IRCS=
    */
	#if ((defined MCU_MK60N512VMD100) || (defined MCU_MK53N512CMD100))
		MCG_C2 = 0;
	#else
		#if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
			MCG_C2 = MCG_C2_RANGE0(2) | MCG_C2_HGO0_MASK | MCG_C2_EREFS0_MASK | MCG_C2_IRCS_MASK;
		#else
			MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK|MCG_C2_IRCS_MASK;
		#endif
	#endif

    /* Select external oscillator and Reference Divider and clear IREFS 
     * to start external oscillator
     * CLKS = 2, FRDIV = 3, IREFS = 0, IRCLKEN = 0, IREFSTEN = 0
     */
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
    
	/* Wait for oscillator to initialize */
	#if((defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7))
		while (!(MCG_S & MCG_S_OSCINIT0_MASK)){};
	#elif defined (MCU_MK40N512VMD100)
		while (!(MCG_S & MCG_S_OSCINIT_MASK)){};
	#endif    
      
	#ifndef MCU_MK20D5
    	/* Wait for Reference Clock Status bit to clear */
    	while (MCG_S & MCG_S_IREFST_MASK) {};
	#endif
    
    /* Wait for clock status bits to show clock source 
     * is external reference clock */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) {};
    
    /* Now in FBE
     * Configure PLL Reference Divider, PLLCLKEN = 0, PLLSTEN = 0, PRDIV = 0x18
     * The crystal frequency is used to select the PRDIV value. 
     * Only even frequency crystals are supported
     * that will produce a 2MHz reference clock to the PLL.
     */
	#if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
    	MCG_C5 = MCG_C5_PRDIV0(BSP_REF_CLOCK_DIV - 1) | MCG_C5_PLLCLKEN0_MASK;
	#else
    	MCG_C5 = MCG_C5_PRDIV(BSP_REF_CLOCK_DIV - 1);
	#endif
    	
    /* Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, 
     * PLL disabled, clock monitor disabled, PLL VCO divider is clear
     */
    MCG_C6 = 0;

    
    /* Calculate mask for System Clock Divider Register 1 SIM_CLKDIV1 */
	#if (defined MCU_MK20D5) || (defined MCU_MK40D7)
		SIM_CLKDIV1 =   SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV - 1) | 	/* core/system clock */
						SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV - 1)  | 	/* peripheral clock; */
						SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV - 1);     /* flash clock */
	#else    
		SIM_CLKDIV1 =  	SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV    - 1) |
						SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV     - 1) |
						SIM_CLKDIV1_OUTDIV3(BSP_FLEXBUS_DIV - 1) |
						SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV   - 1);
	#endif
    
   /* Set the VCO divider and enable the PLL, 
     * LOLIE = 0, PLLS = 1, CME = 0, VDIV = 2MHz * BSP_CLOCK_MUL
     */
	#if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
		MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(BSP_CLOCK_MUL - 24);
	#else
		MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(BSP_CLOCK_MUL - 24);
	#endif
		
    /* Wait for PLL status bit to set */
    while (!(MCG_S & MCG_S_PLLST_MASK)) {};
    
    /* Wait for LOCK bit to set */
	#if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
		while (!(MCG_S & MCG_S_LOCK0_MASK)){}; 	
	#else    
		while (!(MCG_S & MCG_S_LOCK_MASK)) {};
	#endif
    
    /* Now running PBE Mode */

    /* Transition into PEE by setting CLKS to 0
     * CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
     */
    MCG_C1 &= ~MCG_C1_CLKS_MASK;

    /* Wait for clock status bits to update */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) {};

	#if(defined MCU_MK20D5)
    	/* Enable the ER clock of oscillators */
    	OSC0_CR = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;    
	#else
    	/* Enable the ER clock of oscillators */
    	OSC_CR = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;       
    #endif
    
    /* Now running PEE Mode */
    return 0;
#else
    unsigned char frdiv_val;
    unsigned char temp_reg;
    unsigned char prdiv, vdiv;
    short i;
    int ref_freq;
    int pll_freq;

    // If using the PLL as MCG_OUT must check if the MCG is in FEI mode first
    if (mcgout_select)
    {
    	// check if in FEI mode
    	if (!((((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x0) && // check CLKS mux has selcted FLL output
    			(MCG_S & MCG_S_IREFST_MASK) &&                                  // check FLL ref is internal ref clk
    			(!(MCG_S & MCG_S_PLLST_MASK))))                                 // check PLLS mux has selected FLL
    	{
    		return 0x1;                                                     // return error code
    	}
    } // if (mcgout_select)

    // Check if OSC1 is being used as a reference for the MCGOUT PLL
    // This requires a more complicated MCG configuration.
    // At this time (Sept 8th 2011) this driver does not support this option
    if (osc_select && mcgout_select)
    {
    	return 0x80; // Driver does not support using OSC1 as the PLL reference for the system clock on MCGOUT
    }

    // check external frequency is less than the maximum frequency
    if  (crystal_val > 60000000) {return 0x21;}

    // check crystal frequency is within spec. if crystal osc is being used as PLL ref
    if (erefs_val)
    {
    	if ((crystal_val < 8000000) || (crystal_val > 32000000)) {return 0x22;} // return 1 if one of the available crystal options is not available
    }

    // make sure HGO will never be greater than 1. Could return an error instead if desired.
    if (hgo_val > 0)
    {
    	hgo_val = 1; // force hgo_val to 1 if > 0
    }

    // Check PLL divider settings are within spec.
    if ((prdiv_val < 1) || (prdiv_val > 8)) {return 0x41;}
    if ((vdiv_val < 16) || (vdiv_val > 47)) {return 0x42;}

    // Check PLL reference clock frequency is within spec.
    ref_freq = crystal_val / prdiv_val;
    if ((ref_freq < 8000000) || (ref_freq > 32000000)) {return 0x43;}

    // Check PLL output frequency is within spec.
    pll_freq = (crystal_val / prdiv_val) * vdiv_val;
    if ((pll_freq < 180000000) || (pll_freq > 360000000)) {return 0x45;}

    // Determine if oscillator needs to be set up
    if (init_osc)
    {
    	// Check if the oscillator needs to be configured
    	if (!osc_select)
    	{
    		// configure the MCG_C2 register
    		// the RANGE value is determined by the external frequency. Since the RANGE parameter affects the FRDIV divide value
    		// it still needs to be set correctly even if the oscillator is not being used

    		temp_reg = MCG_C2;
    		temp_reg &= ~(MCG_C2_RANGE_MASK | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK); // clear fields before writing new values

    		if (crystal_val <= 8000000)
    		{
    			temp_reg |= (MCG_C2_RANGE(1) | (hgo_val << MCG_C2_HGO_SHIFT) | (erefs_val << MCG_C2_EREFS_SHIFT));
    		}
    		else
    		{
    			// On rev. 1.0 of silicon there is an issue where the the input bufferd are enabled when JTAG is connected.
    			// This has the affect of sometimes preventing the oscillator from running. To keep the oscillator amplitude
    			// low, RANGE = 2 should not be used. This should be removed when fixed silicon is available.
    			//temp_reg |= (MCG_C2_RANGE(2) | (hgo_val << MCG_C2_HGO_SHIFT) | (erefs_val << MCG_C2_EREFS_SHIFT));
    			temp_reg |= (MCG_C2_RANGE(1) | (hgo_val << MCG_C2_HGO_SHIFT) | (erefs_val << MCG_C2_EREFS_SHIFT));
    		}
    		MCG_C2 = temp_reg;
    	}
    	else
    	{
    		// configure the MCG_C10 register
    		// the RANGE value is determined by the external frequency. Since the RANGE parameter affects the FRDIV divide value
    		// it still needs to be set correctly even if the oscillator is not being used
    		temp_reg = MCG_C10;
    		temp_reg &= ~(MCG_C10_RANGE2_MASK | MCG_C10_HGO2_MASK | MCG_C10_EREFS2_MASK); // clear fields before writing new values
    		if (crystal_val <= 8000000)
    		{
    			temp_reg |= MCG_C10_RANGE2(1) | (hgo_val << MCG_C10_HGO2_SHIFT) | (erefs_val << MCG_C10_EREFS2_SHIFT);
    		}
    		else
    		{
    			// On rev. 1.0 of silicon there is an issue where the the input bufferd are enabled when JTAG is connected.
    			// This has the affect of sometimes preventing the oscillator from running. To keep the oscillator amplitude
    			// low, RANGE = 2 should not be used. This should be removed when fixed silicon is available.
    			//temp_reg |= MCG_C10_RANGE2(2) | (hgo_val << MCG_C10_HGO2_SHIFT) | (erefs_val << MCG_C10_EREFS2_SHIFT);
    			temp_reg |= MCG_C10_RANGE2(1) | (hgo_val << MCG_C10_HGO2_SHIFT) | (erefs_val << MCG_C10_EREFS2_SHIFT);
    		}
    		MCG_C10 = temp_reg;
    	} // if (!osc_select)
    } // if (init_osc)

    if (mcgout_select)
    {
    	// determine FRDIV based on reference clock frequency
    	// since the external frequency has already been checked only the maximum frequency for each FRDIV value needs to be compared here.
    	if (crystal_val <= 1250000) {frdiv_val = 0;}
    	else if (crystal_val <= 2500000) {frdiv_val = 1;}
    	else if (crystal_val <= 5000000) {frdiv_val = 2;}
    	else if (crystal_val <= 10000000) {frdiv_val = 3;}
    	else if (crystal_val <= 20000000) {frdiv_val = 4;}
    	else {frdiv_val = 5;}

    	// Select external oscillator and Reference Divider and clear IREFS to start ext osc
    	// If IRCLK is required it must be enabled outside of this driver, existing state will be maintained
    	// CLKS=2, FRDIV=frdiv_val, IREFS=0, IRCLKEN=0, IREFSTEN=0
    	temp_reg = MCG_C1;
    	temp_reg &= ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK); // Clear values in these fields
    	temp_reg = MCG_C1_CLKS(2) | MCG_C1_FRDIV(frdiv_val); // Set the required CLKS and FRDIV values
    	MCG_C1 = temp_reg;

    	// if the external oscillator is used need to wait for OSCINIT to set
    	if (erefs_val)
    	{
    		for (i = 0 ; i < 10000 ; i++)
    		{
    			if (MCG_S & MCG_S_OSCINIT_MASK) break; // jump out early if OSCINIT sets before loop finishes
    		}
    		if (!(MCG_S & MCG_S_OSCINIT_MASK)) return 0x23; // check bit is really set and return with error if not set
    	}

    	// wait for Reference clock Status bit to clear
    	for (i = 0 ; i < 2000 ; i++)
    	{
    		if (!(MCG_S & MCG_S_IREFST_MASK)) break; // jump out early if IREFST clears before loop finishes
    	}
    	if (MCG_S & MCG_S_IREFST_MASK) return 0x11; // check bit is really clear and return with error if not set

    	// Wait for clock status bits to show clock source is ext ref clk
    	for (i = 0 ; i < 2000 ; i++)
    	{
    		if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x2) break; // jump out early if CLKST shows EXT CLK slected before loop finishes
    	}
    	if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) return 0x1A; // check EXT CLK is really selected and return with error if not

    	// Now in FBE
    	// It is recommended that the clock monitor is enabled when using an external clock as the clock source/reference.
    	// It is enabled here but can be removed if this is not required.
    	MCG_C6 |= MCG_C6_CME_MASK;

    	// Select which PLL to enable
    	if (!pll_select)
    	{
    		// Configure PLL0
    		// Ensure OSC0 is selected as the reference clock
    		MCG_C5 &= ~MCG_C5_PLLREFSEL_MASK;
    		//Select PLL0 as the source of the PLLS mux
    		MCG_C11 &= ~MCG_C11_PLLCS_MASK;
    		// Configure MCG_C5
    		// If the PLL is to run in STOP mode then the PLLSTEN bit needs to be OR'ed in here or in user code.
    		temp_reg = MCG_C5;
    		temp_reg &= ~MCG_C5_PRDIV_MASK;
    		temp_reg |= MCG_C5_PRDIV(prdiv_val - 1);    //set PLL ref divider
    		MCG_C5 = temp_reg;

    		// Configure MCG_C6
    		// The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk
    		// The loss of lock interrupt can be enabled by seperately OR'ing in the LOLIE bit in MCG_C6
    		temp_reg = MCG_C6; // store present C6 value
    		temp_reg &= ~MCG_C6_VDIV_MASK; // clear VDIV settings
    		temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV(vdiv_val - 16); // write new VDIV and enable PLL
    		MCG_C6 = temp_reg; // update MCG_C6

    		// wait for PLLST status bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S & MCG_S_PLLST_MASK) break; // jump out early if PLLST sets before loop finishes
    		}
    		if (!(MCG_S & MCG_S_PLLST_MASK)) return 0x16; // check bit is really set and return with error if not set

    		// Wait for LOCK bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S & MCG_S_LOCK_MASK) break; // jump out early if LOCK sets before loop finishes
    		}
    		if (!(MCG_S & MCG_S_LOCK_MASK)) return 0x44; // check bit is really set and return with error if not set

    		// Use actual PLL settings to calculate PLL frequency
    		prdiv = ((MCG_C5 & MCG_C5_PRDIV_MASK) + 1);
    		vdiv = ((MCG_C6 & MCG_C6_VDIV_MASK) + 16);
    	}
    	else
    	{
    		// Configure PLL1
    		// Ensure OSC0 is selected as the reference clock
    		MCG_C11 &= ~MCG_C11_PLLREFSEL2_MASK;
    		//Select PLL1 as the source of the PLLS mux
    		MCG_C11 |= MCG_C11_PLLCS_MASK;
    		// Configure MCG_C11
    		// If the PLL is to run in STOP mode then the PLLSTEN2 bit needs to be OR'ed in here or in user code.
    		temp_reg = MCG_C11;
    		temp_reg &= ~MCG_C11_PRDIV2_MASK;
    		temp_reg |= MCG_C11_PRDIV2(prdiv_val - 1);    //set PLL ref divider
    		MCG_C11 = temp_reg;

    		// Configure MCG_C12
    		// The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk
    		// The loss of lock interrupt can be enabled by seperately OR'ing in the LOLIE2 bit in MCG_C12
    		temp_reg = MCG_C12; // store present C12 value
    		temp_reg &= ~MCG_C12_VDIV2_MASK; // clear VDIV settings
    		temp_reg |=  MCG_C12_VDIV2(vdiv_val - 16); // write new VDIV and enable PLL
    		MCG_C12 = temp_reg; // update MCG_C12
    		// Enable PLL by setting PLLS bit
    		MCG_C6 |= MCG_C6_PLLS_MASK;

    		// wait for PLLCST status bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S2 & MCG_S2_PLLCST_MASK) break; // jump out early if PLLST sets before loop finishes
    		}
    		if (!(MCG_S2 & MCG_S2_PLLCST_MASK)) return 0x17; // check bit is really set and return with error if not set

    		// wait for PLLST status bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S & MCG_S_PLLST_MASK) break; // jump out early if PLLST sets before loop finishes
    		}
    		if (!(MCG_S & MCG_S_PLLST_MASK)) return 0x16; // check bit is really set and return with error if not set

    		// Wait for LOCK bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S2 & MCG_S2_LOCK2_MASK) break; // jump out early if LOCK sets before loop finishes
    		}
    		if (!(MCG_S2 & MCG_S2_LOCK2_MASK)) return 0x44; // check bit is really set and return with error if not set

    		// Use actual PLL settings to calculate PLL frequency
    		prdiv = ((MCG_C11 & MCG_C11_PRDIV2_MASK) + 1);
    		vdiv = ((MCG_C12 & MCG_C12_VDIV2_MASK) + 16);
    	} // if (!pll_select)

    	// now in PBE

    	MCG_C1 &= ~MCG_C1_CLKS_MASK; // clear CLKS to switch CLKS mux to select PLL as MCG_OUT

    	// Wait for clock status bits to update
    	for (i = 0 ; i < 2000 ; i++)
    	{
    		if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x3) break; // jump out early if CLKST = 3 before loop finishes
    	}
    	if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) return 0x1B; // check CLKST is set correctly and return with error if not

    	// Now in PEE
    }
    else
    {
    	// Setup PLL for peripheral only use
    	if (pll_select)
    	{
    		// Setup and enable PLL1
    		// Select ref source
    		if (osc_select)
    		{
    			MCG_C11 |= MCG_C11_PLLREFSEL2_MASK; // Set select bit to choose OSC1
    		}
    		else
    		{
    			MCG_C11 &= ~MCG_C11_PLLREFSEL2_MASK; // Clear select bit to choose OSC0
    		}
    		// Configure MCG_C11
    		// If the PLL is to run in STOP mode then the PLLSTEN2 bit needs to be OR'ed in here or in user code.
    		temp_reg = MCG_C11;
    		temp_reg &= ~MCG_C11_PRDIV2_MASK;
    		temp_reg |= MCG_C11_PRDIV2(prdiv_val - 1);    //set PLL ref divider
    		MCG_C11 = temp_reg;

    		// Configure MCG_C12
    		// The loss of lock interrupt can be enabled by seperately OR'ing in the LOLIE2 bit in MCG_C12
    		temp_reg = MCG_C12; // store present C12 value
    		temp_reg &= ~MCG_C12_VDIV2_MASK; // clear VDIV settings
    		temp_reg |=  MCG_C12_VDIV2(vdiv_val - 16); // write new VDIV and enable PLL
    		MCG_C12 = temp_reg; // update MCG_C12
    		// Now enable the PLL
    		MCG_C11 |= MCG_C11_PLLCLKEN2_MASK; // Set PLLCLKEN2 to enable PLL1

    		// Wait for LOCK bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S2 & MCG_S2_LOCK2_MASK) break; // jump out early if LOCK sets before loop finishes
    		}
    		if (!(MCG_S2 & MCG_S2_LOCK2_MASK)) return 0x44; // check bit is really set and return with error if not set

    		// Use actual PLL settings to calculate PLL frequency
    		prdiv = ((MCG_C11 & MCG_C11_PRDIV2_MASK) + 1);
    		vdiv = ((MCG_C12 & MCG_C12_VDIV2_MASK) + 16);
    	}
    	else
    	{
    		// Setup and enable PLL0
    		// Select ref source
    		if (osc_select)
    		{
    			MCG_C5 |= MCG_C5_PLLREFSEL_MASK; // Set select bit to choose OSC1
    		}
    		else
    		{
    			MCG_C5 &= ~MCG_C5_PLLREFSEL_MASK; // Clear select bit to choose OSC0
    		}
    		// Configure MCG_C5
    		// If the PLL is to run in STOP mode then the PLLSTEN bit needs to be OR'ed in here or in user code.
    		temp_reg = MCG_C5;
    		temp_reg &= ~MCG_C5_PRDIV_MASK;
    		temp_reg |= MCG_C5_PRDIV(prdiv_val - 1);    //set PLL ref divider
    		MCG_C5 = temp_reg;

    		// Configure MCG_C6
    		// The loss of lock interrupt can be enabled by seperately OR'ing in the LOLIE bit in MCG_C6
    		temp_reg = MCG_C6; // store present C6 value
    		temp_reg &= ~MCG_C6_VDIV_MASK; // clear VDIV settings
    		temp_reg |=  MCG_C6_VDIV(vdiv_val - 16); // write new VDIV and enable PLL
    		MCG_C6 = temp_reg; // update MCG_C6
    		// Now enable the PLL
    		MCG_C5 |= MCG_C5_PLLCLKEN_MASK; // Set PLLCLKEN to enable PLL0

    		// Wait for LOCK bit to set
    		for (i = 0 ; i < 2000 ; i++)
    		{
    			if (MCG_S & MCG_S_LOCK_MASK) break; // jump out early if LOCK sets before loop finishes
    		}
    		if (!(MCG_S & MCG_S_LOCK_MASK)) return 0x44; // check bit is really set and return with error if not set

    		// Use actual PLL settings to calculate PLL frequency
    		prdiv = ((MCG_C5 & MCG_C5_PRDIV_MASK) + 1);
    		vdiv = ((MCG_C6 & MCG_C6_VDIV_MASK) + 16);
    	} // if (pll_select)

    } // if (mcgout_select)

    return (((crystal_val / prdiv) * vdiv) / 2); //MCGOUT equals PLL output frequency/2
#endif
}

/* EOF */


