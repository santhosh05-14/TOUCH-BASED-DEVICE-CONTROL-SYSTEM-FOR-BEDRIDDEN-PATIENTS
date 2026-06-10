/* Include required header files */
#include "define.h"
#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "kpmdefines.h"
#include "kpm.h"

/* Keypad lookup table */
u8 KpmLUT[4][4] =
{
    {1,2,3,13},
    {4,5,6,14},
    {7,8,9,15},
    {10,11,12,16}
};

/* Function to initialize keypad */
void InitKPM(void)
{
    /* Configure row pins (P1.16-P1.19) as outputs */
    WRITENIBBLE(IODIR1,ROW0,15);
}

/* Function to scan keypad columns */
u8 ColScan(void)
{
    /* Check whether any key is pressed */
    if((READNIBBLE(IOPIN1,COL0)) < 15)
        return 0;
    else
        return 1;
}

/* Function to identify row number */
u8 RowCheck(void)
{
    u8 rno;

    /* Scan all rows */
    for(rno=0; rno<=3; rno++)
    {
        /* Make one row active at a time */
        WRITENIBBLE(IOPIN1,ROW0,~(1<<rno));

        /* Check for key press */
        if(ColScan() == 0)
        {
            break;
        }
    }

    /* Reset all rows */
    WRITENIBBLE(IOPIN1,ROW0,0x0);

    return rno;
}

/* Function to identify column number */
u8 ColCheck(void)
{
    u8 cno;

    /* Scan all columns */
    for(cno=0; cno<=3; cno++)
    {
        if(STATUSBIT(IOPIN1,(COL0+cno)) == 0)
        {
            break;
        }
    }

    return cno;
}

/* Function to scan and return key value */
u8 KeyScan(void)
{
    u8 keyv, rno, cno;

    /* Wait until a key is pressed */
    while(ColScan());

    /* Get row number */
    rno = RowCheck();

    /* Get column number */
    cno = ColCheck();

    /* Fetch key value from lookup table */
    keyv = KpmLUT[rno][cno];

    /* Wait until key is released */
    while(!ColScan());

    return keyv;
}

/* Function to read a multi-digit number from keypad */
u32 ReadNum(void)
{
    u8 key;
    u32 sum = 0;

    while(1)
    {
        /* Read key value */
        key = KeyScan();

        /* Check whether key is a digit */
        if((key >= '0') && (key <= '9'))
        {
            /* Form the number */
            sum = (sum * 10) + (key - 48);
        }

        /* Exit when 'C' key is pressed */
        else if(key == 'C')
        {
            break;
        }
    }

    return sum;
}