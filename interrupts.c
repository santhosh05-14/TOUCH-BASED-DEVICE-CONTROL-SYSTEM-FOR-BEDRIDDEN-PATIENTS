#include <lpc21xx.h>
#include "types.h"
#include "SPI.h"
#include "define.h"

/* UART receive buffer */
char str[25];

/* Variables to store touch coordinates */
char x[10], y[10], z[10];

/* UART receive character and dummy variable */
char ch, dummy;

/* UART buffer index and receive flag */
unsigned int i = 0, r_flag = 0;

/* Password related variables */
u8 keyvalue;
u8 entered_pass[5];
u8 stored_pass[6];
u8 pass1[5];
u8 pass2[5];

/* EINT3 Interrupt Service Routine */
void eint3_isr(void)__irq
{
    int i, ch;
    u8 key;

    /* Ask user to enter current password */
    CmdLCD(0x01);
    CmdLCD(0x80);
    StrLCD("ENTER CUR PASSWORD");

    CmdLCD(0xC0);

    i = 0;

    /* Read current password */
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

                CmdLCD(0xC0+i);
                CharLCD(' ');
                CmdLCD(0xC0+i);
            }
        }

        /* Enter key */
        else if(key == 16)
        {
            if(i == 4)
                break;
        }

        /* Store password character */
        else
        {
            if(i < 4)
            {
                entered_pass[i] = key;
                CharLCD('*');
                i++;
            }
        }
    }

    entered_pass[4] = '\0';

    /* Read password from EEPROM */
    EEPROM_Read_String(stored_pass);

    while(1)
    {
        /* Validate current password */
        ReadPassword();

        if(!ValidatePassword())
        {
            CmdLCD(0x01);
            CmdLCD(0x80);
            StrLCD("WRONG PASS");

            delay_s(1);
            break;
        }

        /* Ask for new password */
        CmdLCD(0x01);
        CmdLCD(0x80);
        StrLCD("NEW PASSWORD");

        CmdLCD(0xC0);

        i = 0;

        /* Read new password */
        while(1)
        {
            key = KeyScan();

            if(key == 10)
            {
                if(i >= 0)
                {
                    i--;
                    pass1[i] = '\0';

                    CmdLCD(0xC0+i);
                    CharLCD(' ');
                    CmdLCD(0xC0+i);
                }
            }
            else if(key == 16)
            {
                if(i == 4)
                    break;
            }
            else
            {
                if(i < 4)
                {
                    pass1[i] = key;
                    CharLCD('*');
                    i++;
                }
            }
        }

        pass1[4] = '\0';

        delay_ms(1000);

        /* Ask for password confirmation */
        CmdLCD(0x01);
        CmdLCD(0x80);
        StrLCD("CONFIRM PASS");

        CmdLCD(0xC0);

        i = 0;

        /* Read confirmation password */
        while(1)
        {
            key = KeyScan();

            if(key == 10)
            {
                if(i >= 0)
                {
                    i--;
                    pass2[i] = '\0';

                    CmdLCD(0xC0+i);
                    CharLCD(' ');
                    CmdLCD(0xC0+i);
                }
            }
            else if(key == 16)
            {
                if(i == 4)
                    break;
            }
            else
            {
                if(i < 4)
                {
                    pass2[i] = key;
                    CharLCD('*');
                    i++;
                }
            }
        }

        pass2[4] = '\0';

        /* Compare new password and confirmation password */
        if(strcmp(pass1, pass2) == 0)
        {
            /* Update password in EEPROM */
            strcpy(stored_pass, pass1);

            EEPROM_Write_String(stored_pass);

            CmdLCD(0x01);
            delay_ms(5);

            CmdLCD(0x80);
            StrLCD("PASSWORD");

            CmdLCD(0xC0);
            StrLCD("UPDATED");

            delay_s(1);

            /* Display main menu */
            CmdLCD(0x01);
            CmdLCD(0x80);
            StrLCD("TOUCH SCREEN:EN/DIS");

            CmdLCD(0xC0);
            StrLCD("DEVICE1:ON/OFF");

            CmdLCD(0x94);
            StrLCD("DEVICE2:ON/OFF");

            CmdLCD(0xD4);
            StrLCD("DEVICE3:ON/OFF");

            break;
        }
        else
        {
            /* Passwords do not match */
            CmdLCD(0x01);
            CmdLCD(0x80);
            StrLCD("NOT MATCHED");

            delay_s(1);

            continue;
        }
    }

    /* Clear EINT3 interrupt flag */
    SCLRBIT(EXTINT,3);

    /* End of ISR */
    VICVectAddr = 0;
}

/* Function to enable EINT3 interrupt */
void Enable_EINT3(void)
{
    /* Configure P0.20 as EINT3 */
    cfgportpinfunc(0,20,3);

    /* Enable EINT3 interrupt in VIC */
    SSETBIT(VICIntEnable,17);

    /* Configure vector slot */
    VICVectCntl1 = 0x20 | 17;
    VICVectAddr1 = (unsigned)eint3_isr;

    /* Configure edge-triggered interrupt */
    SSETBIT(EXTMODE,3);

    /* Falling edge trigger */
    //SCLRBIT(EXTPOLAR,3);
}

/* UART0 Interrupt Service Routine */
void UART0_isr(void) __irq
{
    /* Check receive interrupt */
    if(U0IIR & 0x04)
    {
        ch = U0RBR;

        /* Store received character */
        if(ch != '\r')
        {
            str[i++] = ch;
        }
        else
        {
            /* End of received string */
            str[i] = '\0';
            i = 0;
            r_flag = 1;
        }
    }
    else
    {
        /* Clear unwanted interrupt */
        dummy = U0IIR;
    }

    /* End of ISR */
    VICVectAddr = 0;
}

/* Function to initialize UART0 */
void InitUART0(void)
{
    /* Configure UART0 TXD and RXD pins */
    PINSEL0 = 0x00000005;

    /* Configure baud rate */
    U0LCR = 0x83;
    U0DLL = 97;
    U0DLM = 0x00;
    U0LCR = 0x03;

    /* Enable receive interrupt */
    U0IER = 0x01;

    /* Configure VIC */
    VICIntSelect = 0x00;
    VICVectCntl0 = 0x20 | 6;
    VICVectAddr0 = (unsigned)UART0_isr;

    /* Enable UART0 interrupt */
    VICIntEnable = (1 << 6);
}
