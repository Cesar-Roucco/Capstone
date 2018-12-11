#include "pushbutton.h"

int pushedButton = 0;

void InitializePushButtonPortPin (void)
{
	P1DIR &= ~BIT3; // reading values
	P1REN |= BIT3; // enabling the pull-up resistor
	P1OUT |= BIT3; // determining if the resistor is pull-up or pull-down
	P1IE |= BIT3; // enabling the interrupt
	P1IES |= BIT3; // selecting the interrupt edge to be high-to-low

}

#pragma vector = PORT1_VECTOR
// Button interrupt service routine
__interrupt void Button_routine(void)
{

	pushedButton = 1 - pushedButton; // 1 - active and 0 - paused

	P1IFG &= ~BIT3;
}
