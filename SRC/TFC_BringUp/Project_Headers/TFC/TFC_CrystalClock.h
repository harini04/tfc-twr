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



int pll_init();

#endif /* TFC_CRYSTALCLOCK_H_ */
