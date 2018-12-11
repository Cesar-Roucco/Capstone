#include "timerA.h"
#include "LED.h"

void ConfigureTimerA(void)
{
	TA0CTL = (MC_0 | TACLR);
	TA0CTL |= (TASSEL_2 | ID_3 | MC_1 | TAIE);

	TA0CCR0 = 249;
	TA0CCR1 = 1;

	// Enable Interrupt
	TA0CCTL0 |= CCIE;
	TA0CCTL1 |= CCIE;
}

#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG0
	__interrupt void Timer0_A0_routine(void)
{
}

#pragma vector = TIMER0_A1_VECTOR
// Interrupt service routine for CCIFG1 and TAIFG
	__interrupt void Timer0_A1_routine(void)
{
	switch (TAIV){
	case TA0IV_NONE:
		break;
	case TA0IV_TACCR1: // CCIFG1 interrupt
		TURN_OFF_LED;
		break;
	case TA0IV_TAIFG: // TAIFG interrupt
		TURN_ON_LED;
		break;
	default: for (;;); // Should not be possible
	}
}
