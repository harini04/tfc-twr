//See Kinetis Quick User Guide Page 37!!

#ifndef ARM_CM4_H_
#define ARM_CM4_H_


#include "derivative.h" /* include peripheral declarations */

void stop (void);
void wait (void);
void write_vtor (int vtor);
void enable_irq (int irq);
void disable_irq (int irq);
void set_irq_priority (int irq, int prio);

/***********************************************************************/
#endif /* ARM_CM4_H_ */
