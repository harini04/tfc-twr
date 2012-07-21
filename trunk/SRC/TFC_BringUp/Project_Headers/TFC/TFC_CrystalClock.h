/*
 * TFC_CrystalClock.h
 *
 *  Created on: Apr 13, 2012
 *      Author: emh203
 */

#ifndef TFC_CRYSTALCLOCK_H_
#define TFC_CRYSTALCLOCK_H_


#pragma define_section relocate_code ".data" ".app_data" ".data" far_abs RX
#define __relocate_code__   __declspec(relocate_code)
void __relocate_code__ TFC_InitClock();


#define CORE_CLOCK			 (96000000)
#define PERIPHERAL_BUS_CLOCK (CORE_CLOCK/2)

#define BSP_CLOCK_SRC                   (8000000ul)       	// crystal, oscillator freq.
#define BSP_REF_CLOCK_SRC               (2000000ul)       		// must be 2-4MHz

#define BSP_CORE_DIV                    (1)
#define BSP_BUS_DIV                     (2)
#define BSP_FLEXBUS_DIV                 (2)
#define BSP_FLASH_DIV                   (4)

// BSP_CLOCK_MUL from interval 24 - 55
#define BSP_CLOCK_MUL                   (48)    // 48MHz

#define BSP_REF_CLOCK_DIV               (BSP_CLOCK_SRC / BSP_REF_CLOCK_SRC)
#define BSP_CLOCK                       (BSP_REF_CLOCK_SRC * BSP_CLOCK_MUL)
#define BSP_CORE_CLOCK                  (BSP_CLOCK / BSP_CORE_DIV)          // CORE CLK, max 100MHz
#define BSP_SYSTEM_CLOCK                (BSP_CORE_CLOCK)                    // SYSTEM CLK, max 100MHz
#define BSP_BUS_CLOCK                   (BSP_CLOCK / BSP_BUS_DIV)       // max 50MHz
#define BSP_FLEXBUS_CLOCK               (BSP_CLOCK / BSP_FLEXBUS_DIV)
#define BSP_FLASH_CLOCK                 (BSP_CLOCK / BSP_FLASH_DIV)     // max 25MHz


int pll_init();

#endif /* TFC_CRYSTALCLOCK_H_ */
