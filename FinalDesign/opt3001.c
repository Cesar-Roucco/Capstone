#include <msp430g2553.h>
#include "opt3001.h"
#include "TI_USCI_I2C_master.h"

unsigned char init_buffer[3] = {CONFIG_REG, DEFAULT_CONFIG_MSB, DEFAULT_CONFIG_LSB};

void OPT3001_Init(void) {

	TI_USCI_I2C_transmitinit(OPT_ADDR,10);
	while(TI_USCI_I2C_notready());
	TI_USCI_I2C_transmit(3,init_buffer);

}

void OPT3001_SetReadRegister(unsigned char *regName, unsigned char bytes) {

	TI_USCI_I2C_transmitinit(OPT_ADDR,10);
	while(TI_USCI_I2C_notready());
	TI_USCI_I2C_transmit(bytes,regName);

}

int OPT3001_ReadLuxValues(void) {

	int result;
	unsigned char read_buffer[2] = {0x00, 0x00};

	//__bis_SR_register(LPM0_bits|GIE);
	TI_USCI_I2C_receiveinit(OPT_ADDR,10);
	while ( TI_USCI_I2C_notready() );
	TI_USCI_I2C_receive(2, read_buffer);
	//LPM0;

	result = (read_buffer[0] << 8) | read_buffer[1];

	return result;
}
