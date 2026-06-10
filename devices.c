#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#include "define.h"

/* Touch screen enable/disable flag */
int touchenable = 0;

/* Device status flags */
int touchflag1 = 0;
int touchflag2 = 0;
int touchflag3 = 0;
int touchflag4 = 0;

/* Function to control Device 1 */
void device1(void)
{
    /* Increment device 1 status flag */
    touchflag1++;

    /* Turn ON Device 1 */
    if(touchflag1 == 1)
    {
        CmdLCD(0xC0);
        StrLCD("DEVICE1:ON    ");

        IOSET1 = LED1;

        /* Keep Device 2 ON if already enabled */
        if(touchflag2)
        {
            IOSET1 = LED2;
        }
    }

    /* Turn OFF Device 1 */
    else if(touchflag1 == 2)
    {
        CmdLCD(0xC0);
        StrLCD("DEVICE1:OFF   ");

        IOCLR1 = LED1;

        /* Keep Device 2 ON if already enabled */
        if(touchflag2)
        {
            IOSET1 = LED2;
        }

        touchflag1 = 0;
    }
}

/* Function to control Device 2 */
void device2(void)
{
    /* Increment device 2 status flag */
    touchflag2++;

    /* Turn ON Device 2 */
    if(touchflag2 == 1)
    {
        CmdLCD(0x94);
        StrLCD("DEVICE2:ON    ");

        IOSET1 = LED2;

        /* Keep Device 1 ON if already enabled */
        if(touchflag1)
        {
            IOSET1 = LED1;
        }
    }

    /* Turn OFF Device 2 */
    else if(touchflag2 == 2)
    {
        CmdLCD(0x94);
        StrLCD("DEVICE2:OFF    ");

        IOCLR1 = LED2;

        /* Keep Device 1 ON if already enabled */
        if(touchflag1)
        {
            IOSET1 = LED1;
        }

        touchflag2 = 0;
    }
}

/* Function to control Device 3 (Buzzer) */
void device3(void)
{
    /* Check whether buzzer is OFF */
    if(touchflag3 == 0)
    {
        touchflag3 = 1;

        CmdLCD(0xD4);
        StrLCD("DEVICE3:ON     ");

        /* Turn ON buzzer */
        IOSET0 = BUZZER;

        /* Buzzer ON for 2 seconds */
        delay_s(2);

        /* Turn OFF buzzer */
        IOCLR0 = BUZZER;

        touchflag3 = 0;

        CmdLCD(0xD4);
        StrLCD("DEVICE3:OFF   ");
    }
}

/* Function to update device status when touch screen is disabled */
void disable(void)
{
    /* Check Device 1 status */
    if(touchflag1 == 1)
    {
        CmdLCD(0xC0);
        StrLCD("DEVICE1:ON     ");

        IOSET1 = LED1;

        if(touchflag2)
        {
            IOSET1 = LED2;
        }
    }
    else if(touchflag1 == 2)
    {
        CmdLCD(0xC0);
        StrLCD("DEVICE1:OFF    ");

        IOCLR1 = LED1;

        if(touchflag2)
        {
            IOSET1 = LED2;
        }

        touchflag1 = 0;
    }

    /* Check Device 2 status */
    if(touchflag2 == 1)
    {
        CmdLCD(0x94);
        StrLCD("DEVICE2:ON    ");

        IOSET1 = LED2;

        if(touchflag1)
        {
            IOSET1 = LED1;
        }
    }
    else if(touchflag2 == 2)
    {
        CmdLCD(0x94);
        StrLCD("DEVICE2:OFF    ");

        IOCLR1 = LED2;

        if(touchflag1)
        {
            IOSET1 = LED1;
        }

        touchflag2 = 0;
    }

    /* Display Device 3 status as OFF */
    if(touchflag3 == 0)
    {
        CmdLCD(0xD4);
        StrLCD("DEVICE3:OFF    ");
    }
}


