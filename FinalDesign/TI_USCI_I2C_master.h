// I2C code
#ifndef TI_USCI_I2C_MASTER_H_
#define TI_USCI_I2C_MASTER_H_

#include <msp430g2553.h>
#define SDA_PIN		BIT7
#define SCL_PIN		BIT6

void TI_USCI_I2C_receiveinit(unsigned char slave_address, unsigned char prescale);
void TI_USCI_I2C_transmitinit(unsigned char slave_address, unsigned char prescale);

void TI_USCI_I2C_receive(unsigned char byteCount, unsigned char *field);
void TI_USCI_I2C_transmit(unsigned char byteCount, unsigned char *field);

unsigned char TI_USCI_I2C_slave_present(unsigned char slave_address);
unsigned char TI_USCI_I2C_notready();

#endif /* TI_USCI_I2C_MASTER_H_ */
