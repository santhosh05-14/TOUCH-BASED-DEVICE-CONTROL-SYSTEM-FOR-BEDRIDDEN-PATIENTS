/* Header file for SPI and EEPROM function declarations */

#include "types.h"

/* Function to initialize SPI peripheral */
void Init_SPI(void);

/* Function to transmit and receive one byte through SPI */
u8 spi(u8 sDat);

/* Function to enable EEPROM write operation */
void WriteEnable(void);

/* Function to disable EEPROM write operation */
void WriteDisable(void);

/* Function to write data bytes into EEPROM */
void spi_eeprom_bytewrite(u16 wBuffAddr, u8 *p, u16 nbytes);

/* Function to read data bytes from EEPROM */
u8* spi_eeprom_byteread(u16 rBuffAddr, u8 *p, u16 nbytes);