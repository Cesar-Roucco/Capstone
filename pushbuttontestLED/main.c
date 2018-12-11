#include <msp430.h>

#define LED BIT6
#define BUTTON BIT3

// Function prototypes
void ConfigureClockModule(void);

void main(void){
	WDTCTL = WDTPW|WDTHOLD;
    P1DIR = LED;
	P1REN = BUTTON;
	P1OUT = BUTTON;

	while(1){
		if((P1IN & BUTTON) == 0x00){
			__delay_cycles(5000);
			if((P1IN & BUTTON) == 0x00){
				P1OUT ^= LED;
				while((P1IN & BUTTON) == 0x00);
			}
		}
	}
}
