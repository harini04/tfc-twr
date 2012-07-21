
#include "TFC\TFC.h"

static void wdog_disable(void)
{
	/* Write 0xC520 to the unlock register */
	WDOG_UNLOCK = 0xC520;
	
	/* Followed by 0xD928 to complete the unlock */
	WDOG_UNLOCK = 0xD928;
	
	/* Clear the WDOGEN bit to disable the watchdog */
	WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
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
static int pll_init()
{

	MCG_C2 = MCG_C2_RANGE(2) | MCG_C2_HGO_MASK | MCG_C2_EREFS_MASK|MCG_C2_IRCS_MASK;

    /* Select external oscillator and Reference Divider and clear IREFS 
     * to start external oscillator
     * CLKS = 2, FRDIV = 3, IREFS = 0, IRCLKEN = 0, IREFSTEN = 0
     */
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
    	/* Wait for Reference Clock Status bit to clear */
    	while (MCG_S & MCG_S_IREFST_MASK) {};
    
    /* Wait for clock status bits to show clock source 
     * is external reference clock */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) {};
    
    /* Now in FBE
     * Configure PLL Reference Divider, PLLCLKEN = 0, PLLSTEN = 0, PRDIV = 0x18
     * The crystal frequency is used to select the PRDIV value. 
     * Only even frequency crystals are supported
     * that will produce a 2MHz reference clock to the PLL.
     */
		MCG_C5 = MCG_C5_PRDIV(BSP_REF_CLOCK_DIV - 1);
		
    /* Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, 
     * PLL disabled, clock monitor disabled, PLL VCO divider is clear
     */
    MCG_C6 = 0;

    
    /* Calculate mask for System Clock Divider Register 1 SIM_CLKDIV1 */
    SIM_CLKDIV1 =  	SIM_CLKDIV1_OUTDIV1(BSP_CORE_DIV    - 1) |
						SIM_CLKDIV1_OUTDIV2(BSP_BUS_DIV     - 1) |
						SIM_CLKDIV1_OUTDIV3(BSP_FLEXBUS_DIV - 1) |
						SIM_CLKDIV1_OUTDIV4(BSP_FLASH_DIV   - 1);

   /* Set the VCO divider and enable the PLL, 
     * LOLIE = 0, PLLS = 1, CME = 0, VDIV = 2MHz * BSP_CLOCK_MUL
     */
		MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(BSP_CLOCK_MUL - 24);
		
    /* Wait for PLL status bit to set */
    while (!(MCG_S & MCG_S_PLLST_MASK)) {};
    
		while (!(MCG_S & MCG_S_LOCK_MASK)) {};
    
    /* Now running PBE Mode */

    /* Transition into PEE by setting CLKS to 0
     * CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
     */
    MCG_C1 &= ~MCG_C1_CLKS_MASK;

    /* Wait for clock status bits to update */
    while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) {};

	/* Enable the ER clock of oscillators */
    	OSC_CR = OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;       
    
    /* Now running PEE Mode */
    return 0;

}


void TFC_InitClock()
{
	pll_init();
	 /* SIM Configuration */

	/************* USB Part **********************/
	/*********************************************/   
	SIM_CLKDIV2 &= (uint32_t)(~(SIM_CLKDIV2_USBFRAC_MASK | SIM_CLKDIV2_USBDIV_MASK));

	/* Configure USBFRAC = 0, USBDIV = 0 => frq(USBout) = 1 / 1 * frq(PLLin) */
	SIM_CLKDIV2 = SIM_CLKDIV2_USBDIV(1);
	    
	/* Configure USB to be clocked from PLL */
	SIM_SOPT2  |= (SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);

	/* Enable USB-OTG IP clocking */
	SIM_SCGC4 |= (SIM_SCGC4_USBOTG_MASK); 
	    
	/* Configure enable USB regulator for device */
	//SIM_SOPT1 |= SIM_SOPT1_USBREGEN_MASK;

	    
	NVICICER2 |= (1<<9);	/* Clear any pending interrupts on USB */
	NVICISER2 |= (1<<9);	/* Enable interrupts from USB module */	 

		
}
	

