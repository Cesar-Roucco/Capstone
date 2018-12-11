#ifndef PIR_H
#define PIR_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 PIR
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.3
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define PIR_BIT					BIT3
#define PIR_PORT				P1IN
#define PIR_DDR					P1DIR
#define SET_PIR_AS_AN_INPUT		PIR_DDR &= ~PIR_BIT
#define READ_PIR_VAL			PIR_PORT & PIR_BIT

// Prototypes
void InitializePIRPortPin(void);

#endif
