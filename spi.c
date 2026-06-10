/* Include required header files */
#include "SPI_defines.h"
#include <lpc21xx.h>
#include "pinconnectblock.h"
#include "delay.h"

/* Function to initialize SPI peripheral */
void Init_SPI(void)
{
    /* Configure P0.4 as SCK */
    cfgportpinfunc(0,4,1);

    /* Configure P0.5 as MOSI */
    cfgportpinfunc(0,5,1);

    /* Configure P0.6 as MISO */
    cfgportpinfunc(0,6,1);

    /* Make CS pin high */
    IOSET0 = 1 << CS;

    /* Configure CS pin as output */
    IODIR0 = 1 << CS;

    /* Set SPI clock frequency */
    S0SPCCR = LOADVAL;

    /* Configure SPI as Master Mode and Mode-3 */
    S0SPCR = (1 << MSTR) | (3 << CPHA);
}

/* Function to transmit and receive one byte through SPI */
u8 spi(u8 sDat)
{
    /* Load data into SPI data register */
    S0SPDR = sDat;

    /* Wait until transmission completes */
    while(((S0SPSR >> SPIF) & 1) == 0);

    /* Return received data */
    return S0SPDR;
}

/* Function to enable EEPROM write operation */
void WriteEnable(void)
{
    /* Select EEPROM */
    IOCLR0 = 1 << CS;

    /* Send Write Enable command */
    spi(WREN);

    /* Deselect EEPROM */
    IOSET0 = 1 << CS;
}

/* Function to disable EEPROM write operation */
void WriteDisable(void)
{
    /* Select EEPROM */
    IOCLR0 = 1 << CS;

    /* Send Write Disable command */
    spi(WRDI);

    /* Deselect EEPROM */
    IOSET0 = 1 << CS;
}

/* Function to write bytes into EEPROM */
void spi_eeprom_bytewrite(u16 wBuffAddr, u8 *p, u16 nbytes)
{
    u16 i;

    /* Enable write latch */
    WriteEnable();

    /* Select EEPROM */
    IOCLR0 = 1 << CS;

    /* Send WRITE command */
    spi(WRITE);

    /* Send EEPROM address (MSB) */
    spi(wBuffAddr >> 8);

    /* Send EEPROM address (LSB) */
    spi(wBuffAddr);

    /* Write data bytes */
    for(i = 0; i < nbytes; i++)
    {
        spi(p[i]);
    }

    /* Deselect EEPROM */
    IOSET0 = 1 << CS;

    /* Wait for internal write cycle */
    delay_ms(5);

    /* Disable write latch */
    WriteDisable();
}

/* Function to read bytes from EEPROM */
u8* spi_eeprom_byteread(u16 rBuffAddr, u8 *p, u16 nbytes)
{
    u16 i;

    /* Select EEPROM */
    IOCLR0 = 1 << CS;

    /* Send READ command */
    spi(READ);

    /* Send EEPROM address (MSB) */
    spi(rBuffAddr >> 8);

    /* Send EEPROM address (LSB) */
    spi(rBuffAddr);

    /* Read data bytes */
    for(i = 0; i < nbytes; i++)
    {
        p[i] = spi(0x00);
    }

    /* Deselect EEPROM */
    IOSET0 = 1 << CS;

    /* Return received buffer */
    return p;
}