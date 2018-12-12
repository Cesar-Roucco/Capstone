#include <msp430.h>
#include "LED.h"
#include "pir.h"
#include "TI_USCI_I2C_master.h"
#include "opt3001.h"

// Function prototypes
void ConfigureClockModule(void);
unsigned char result_reg[1] = {RESULT_REG};
unsigned char read_buffer[2] = {0x00, 0x00};
unsigned int result;
unsigned short raw, exp, mnt, msb, lsb;


void main(void){
    // Stop the watchdog timer, and configure the clock module.
    WDTCTL = WDTPW + WDTHOLD;
    ConfigureClockModule();

    // Initialize port pins associated with the PIR and LED.
    InitializePIRPortPin();
    InitializeLEDPortPin();

    // Configure timer A to generate the required interrupt.
//    _enable_interrupts();
	_EINT();

    // Set Output to P2.1
    P2DIR |= 0x02; // Set pin 2.1 to the output direction.
    P2SEL |= 0x02; // Select pin 2.1 as our PWM output.

    // PWM
    TA1CCR0 = 249; // Set the period in the Timer A0 Capture/Compare 0 register to 249us.
    TA1CCTL1 = OUTMOD_7;

    OPT3001_Init();
	while(TI_USCI_I2C_notready());

	OPT3001_SetReadRegister(result_reg,1);
	while(TI_USCI_I2C_notready());

	TI_USCI_I2C_receiveinit(OPT_ADDR,10);

	// Infinite loop
    while (1) {
    	while ( TI_USCI_I2C_notready() );
		TI_USCI_I2C_receive(2, read_buffer);

		msb = read_buffer[0] << 8;
		lsb = read_buffer[1];
		raw = msb | lsb;

		result = raw&0x0FFF;
		exp = (raw>>12)&0x000F;

		//convert raw readings to LUX
		switch(exp){
			case 0: //*0.015625
				result = result>>6;
				break;
			case 1: //*0.03125
				result = result>>5;
				break;
			case 2: //*0.0625
				result = result>>4;
				break;
			case 3: //*0.125
				result = result>>3;
				break;
			case 4: //*0.25
				result = result>>2;
				break;
			case 5: //*0.5
				result = result>>1;
				break;
			case 6:
				result = result;
				break;
			case 7: //*2
				result = result<<1;
				break;
			case 8: //*4
				result = result<<2;
				break;
			case 9: //*8
				result = result<<3;
				break;
			case 10: //*16
				result = result<<4;
				break;
			case 11: //*32
				result = result<<5;
				break;
		}

    	// If motion ... turn it "on"
    	if ((1)){
    		if(result < 1300){
    			TA1CCR1 = 50; // The period in microseconds that the power is ON. It's half the time, which translates to a 20% duty cycle.
    		}
    		else if(result >= 100 && result <= 200){
    			TA1CCR1 = 25;
    		}
    		else if(result >= 201 && result <= 500){
    			TA1CCR1 = 10;
    		}
    		else{
    			TA1CCR1 = 0;
    		}
    		_delay_cycles(1000000 * 5); // holds the light for 5 seconds
    	}

    	// If no Motion ... turn it "off"
    	else {
		    TA1CCR1 = 0; // The period in microseconds that the power is ON. It's half the time, which translates to a 0% duty cycle.
    	}

    	TA1CTL = TASSEL_2 + MC_1; // TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in TA0CCR0.
    }
}

void ConfigureClockModule(void){
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations.
    DCOCTL  = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    //BCSCTL2 |= DIVS_3;
}
