#ifndef LED_H
#define LED_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 LED
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.0
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define LED_BIT					BIT0
#define LED_PORT				P1OUT
#define LED_DDR					P1DIR
#define SET_LED_AS_AN_OUTPUT	LED_DDR |= LED_BIT
#define TURN_ON_LED				LED_PORT |= LED_BIT
#define TURN_OFF_LED			LED_PORT &= ~LED_BIT
#define TOGGLE_LED				LED_PORT ^= LED_BIT

// Prototypes
void InitializeLEDPortPin(void);

#endif
