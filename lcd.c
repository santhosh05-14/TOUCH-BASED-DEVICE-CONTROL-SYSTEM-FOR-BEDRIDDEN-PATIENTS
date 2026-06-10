/* Include required header files */
#include "define.h"
#include "types.h"
#include <lpc21xx.h>
#include "lcd_defines.h"
#include "delay.h"

/* Function to write data/command to LCD */
void WriteLCD(u8 data)
{
    /* Select write operation */
    SCLRBIT(IOCLR0,RW);

    /* Put data on LCD data pins */
    WRITEBYTE(IOPIN0,LCD_DATA,data);

    /* Generate enable pulse */
    SSETBIT(IOSET0,EN);
    delay_us(1);
    SCLRBIT(IOCLR0,EN);

    /* Wait for LCD internal processing */
    delay_ms(2);
}

/* Function to send command to LCD */
void CmdLCD(u8 cmd)
{
    /* Select command register */
    SCLRBIT(IOCLR0,RS);

    /* Send command */
    WriteLCD(cmd);
}

/* Function to display a character on LCD */
void CharLCD(u8 ascii)
{
    /* Select data register */
    SSETBIT(IOSET0,RS);

    /* Send character */
    WriteLCD(ascii);
}

/* Function to initialize LCD */
void InitLCD(void)
{
    /* Configure data pins as output */
    WRITEBYTE(IODIR0,LCD_DATA,0xFF);

    /* Configure control pins as output */
    SETBIT(IODIR0,RS);
    SETBIT(IODIR0,RW);
    SETBIT(IODIR0,EN);

    /* LCD initialization sequence */
    delay_ms(15);

    CmdLCD(MODE_8BIT_1LINE);
    delay_ms(5);

    CmdLCD(MODE_8BIT_1LINE);
    delay_us(100);

    CmdLCD(MODE_8BIT_1LINE);

    CmdLCD(MODE_8BIT_2LINE);
    CmdLCD(DISP_ON_CUR_OFF);
    CmdLCD(CLEAR_LCD);
    CmdLCD(SHIFT_CUR_RIGHT);
    CmdLCD(0x02);
}

/* Function to display a string on LCD */
void StrLCD(u8 *str)
{
    while(*str)
    {
        CharLCD(*str++);
    }
}

/* Function to display unsigned integer on LCD */
void U32LCD(u32 n)
{
    u8 a[10];
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            a[i++] = (n % 10) + '0';
            n /= 10;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}

/* Function to display signed integer on LCD */
void S32LCD(s32 n)
{
    if(n < 0)
    {
        n = -n;

        CharLCD('-');

        U32LCD(n);
    }
}

/* Function to display binary value on LCD */
void BinLCD(u32 n, u8 nbd)
{
    s32 i;

    for(i = (nbd - 1); i >= 0; i--)
    {
        CharLCD(((n >> i) & 1) + 48);
    }
}

/* Function to build custom characters in CGRAM */
void BuildCGRAM(u8 *p, u8 nBytes)
{
    s32 i;

    /* Select CGRAM */
    CmdLCD(GOTO_CGRAM);

    for(i = 0; i < nBytes; i++)
    {
        CharLCD(p[i]);
    }

    /* Return to DDRAM */
    CmdLCD(GOTO_LINE2_POS0);
}

/* Function to display floating point number on LCD */
void f32LCD(f32 fnum, u8 ndp)
{
    u32 inum;

    if(fnum < 0.0)
    {
        CharLCD('-');
        fnum = -fnum;
    }

    inum = fnum;

    U32LCD(inum);

    CharLCD('.');

    while(ndp)
    {
        fnum = (fnum - inum) * 10;

        inum = fnum;

        CharLCD(inum + 48);

        ndp--;
    }
}

/* Function to display hexadecimal number on LCD */
void HexLCD(u32 n)
{
    u8 a[8], rem;
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            rem = n % 16;

            (rem < 10) ? (rem += 48) : (rem += 55);

            a[i++] = rem;

            n /= 16;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}

/* Function to display octal number on LCD */
void OctLCD(u32 n)
{
    s32 i = 0;
    u8 a[12];

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            a[i++] = (n % 8) + 48;

            n /= 8;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}