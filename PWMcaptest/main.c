#include <msp430.h>
#include "LED.h"
#include "timerA.h"
#include "pir.h"

// Function prototypes
void ConfigureClockModule(void);

void main(void){
    // Stop the watchdog timer, and configure the clock module.
    WDTCTL = WDTPW + WDTHOLD;
    ConfigureClockModule();

    // Initialize port pins associated with the PIR and LED.
    InitializePIRPortPin();
    InitializeLEDPortPin();

    // Configure timer A to generate the required interrupt.
    ConfigureTimerA();
    _enable_interrupts();

    // Infinite loop
    while (1) {

    	// If motion ... turn it "on"
    	if (!(READ_PIR_VAL)){
    		TURN_ON_LED;
    	}
    	// If no Motion ... turn it "off"
    	else {
    		TURN_OFF_LED;
    	}
    }
}

void ConfigureClockModule(void){
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations.
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 |= DIVS_3;
}
