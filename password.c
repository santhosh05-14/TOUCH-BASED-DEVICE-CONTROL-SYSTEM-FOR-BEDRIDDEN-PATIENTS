/* Include required header files */
#include <lpc21xx.h>
#include "types.h"
#include "SPI.h"
#include "delay.h"

/* External password variables */
extern u8 keyvalue;
extern u8 entered_pass[5];
extern u8 stored_pass[6];
extern u8 pass1[5];
extern u8 pass2[5];

/* Function to read password from EEPROM */
void ReadPassword(void)
{
    /* Read 4-byte password from EEPROM */
    spi_eeprom_byteread(0x0000, stored_pass, 4);

    /* Add string terminator */
    stored_pass[5] = '\0';
}

/* Function to get password from keypad */
void GetPassword(void)
{
    int i, ch;
    u8 key;

    /* Display password prompt */
    CmdLCD(0x01);

    CmdLCD(0x80);
    StrLCD("ENTER PASSWORD");

    CmdLCD(0xC0);

    i = 0;

    /* Read 4-digit password */
    while(1)
    {
        key = KeyScan();

        /* Backspace key */
        if(key == 10)
        {
            if(i >= 0)
            {
                i--;

                entered_pass[i] = '\0';

                CmdLCD(0xC0 + i);
                CharLCD(' ');

                CmdLCD(0xC0 + i);
            }
        }

        /* Enter key */
        else if(key == 16)
        {
            if(i == 4)
                break;
        }

        /* Store password digit */
        else
        {
            if(i < 4)
            {
                entered_pass[i] = key;

                /* Display '*' instead of actual password */
                CharLCD('*');

                i++;
            }
        }
    }

    /* Add string terminator */
    entered_pass[4] = '\0';
}

/* Function to validate entered password */
u8 ValidatePassword(void)
{
    int i;

    /* Compare entered password with stored password */
    for(i = 0; i < 4; i++)
    {
        if(entered_pass[i] != stored_pass[i])
        {
            return 0;
        }
    }

    return 1;
}

/* Function to store default password in EEPROM */
void StorePassword(void)
{
    u8 pass[4] = {1,2,3,4};

    /* Write default password */
    spi_eeprom_bytewrite(0x0000, pass, 4);
}

/* Function to read password string from EEPROM */
void EEPROM_Read_String(u8 *p)
{
    /* Read password from EEPROM */
    spi_eeprom_byteread(0x0000, p, 4);

    /* Add string terminator */
    p[4] = '\0';
}

/* Function to write updated password into EEPROM */
void EEPROM_Write_String(u8 *p)
{
    /* Write password to EEPROM */
    spi_eeprom_bytewrite(0x0000, p, 4);
}