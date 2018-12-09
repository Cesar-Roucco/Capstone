#include <msp430.h>
#include "LED.h"
#define TRUE 1

// Function prototypes
void ConfigureClockModule(void);

void main(void)
{
	// Stop the watchdog timer, and configure the clock module.
	WDTCTL = WDTPW + WDTHOLD;
	ConfigureClockModule();
	    
    InitializeLEDPortPins();

	// Infinite loop
  	while (TRUE)
  	{
  		TURN_ON_LED1;
  		TURN_ON_LED2;
  	}
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations.
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}
