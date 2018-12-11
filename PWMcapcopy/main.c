#include <msp430.h>
#include "LED.h"
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
    _enable_interrupts();

    // Set Output to P1.6
    P1DIR |= BIT6; // Set pin 1.6 to the output direction.
    P1SEL |= BIT6; // Select pin 1.6 as our PWM output.

    // PWM
    TA0CCR0 = 249; // Set the period in the Timer A0 Capture/Compare 0 register to 249 us.
    TA0CCTL1 = OUTMOD_7;

    // Infinite loop
    while (1) {

    	// If motion ... turn it "on"
    	if ((READ_PIR_VAL)){
		    TA0CCR1 = 25; // The period in microseconds that the power is ON. It's half the time, which translates to a 2% duty cycle.
    	}

    	// If no Motion ... turn it "off"
    	else {
		    TA0CCR1 = 0; // The period in microseconds that the power is ON. It's half the time, which translates to a 0% duty cycle.
    	}

    	TA0CTL = TASSEL_2 + MC_1; // TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in TA0CCR0.
    }
}

void ConfigureClockModule(void){
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations.
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL2 |= DIVS_3;
}
