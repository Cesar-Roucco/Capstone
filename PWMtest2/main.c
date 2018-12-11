#include <msp430.h>
#include "LED.h"
#include "pushbutton.h"
#include "timerA.h"

// Global variable
char LEDBit = LED1;

// Function prototypes
void ConfigureClockModule(void);

void main(void)
{
    // Stop the watchdog timer, and configure the clock module.
    WDTCTL = WDTPW + WDTHOLD;
    ConfigureClockModule();

    // Initialize port pins associated with the LEDs, and then turn off LEDs.
    InitializeLEDPortPins();

    // Initialize the port pin associated with the pushbutton
    InitializePushButtonPortPin();

    // Configure timer A to generate the required interrupt.
    ConfigureTimerA();

    _enable_interrupts();

    // Infinite loop
    while (1) {
    	if(pushedButton == 1){
    		TURN_ON_LED1;
    	}
    	if(pushedButton == 0){
    		TURN_OFF_LED1;
    	}
    }
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations.
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 |= DIVS_3;
}

