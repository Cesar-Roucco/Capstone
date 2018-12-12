
#ifndef OPT3001_H_
#define OPT3001_H_

// OPT3001 Address Bytes
#define OPT_ADDR	0x44

// OPT3001 Register Addresses
#define RESULT_REG  0x00
#define CONFIG_REG  0x01
#define LOW_LIMIT   0x02
#define HIGH_LIMIT  0x03
#define MANUFACTURER_ID_REG 0x7E
#define DEVICE_ID_REG   0x7F

// OPT3001 Configuration Values
#define DEFAULT_CONFIG_MSB 		0b11001100	 // 800ms
#define DEFAULT_CONFIG_LSB 		0b00010000

// Function definitions
void OPT3001_Init(void);
void OPT3001_SetReadRegister(unsigned char *regName, unsigned char bytes);
int OPT3001_ReadLuxValues(void);
//int OPT3001_ReadFromRegister(void);

#endif /* OPT3001_H_ */
