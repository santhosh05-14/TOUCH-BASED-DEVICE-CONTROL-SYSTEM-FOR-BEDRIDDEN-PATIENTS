#include <LPC21XX.H>
#include<string.h>
#include "devices.h"
#include "pinconnectblock.h"
#include "define.h"
#include "lcd.h"
#include "kpm.h"
#include "SPI.h"
#include "delay.h"
#include "types.h"
#include "password.h"
#include "interrupts.h"
extern int touchenable;
extern int touchflag1; 
extern int touchflag2;
extern int touchflag3;
extern int touchflag4;
extern char str[25];
extern char x[10],y[10],z[10];
extern char ch,dummy;
extern unsigned int i,r_flag;
extern u8 keyvalue;
extern u8 entered_pass[5];
extern u8 stored_pass[6];
extern u8 pass1[5];
extern u8 pass2[5];

/* Main function */
int main()
{
    int i,j,k,a,b,c;

    /* Configure LED pins as output */
    IODIR1 |= LED1 | LED2;

    /* Configure buzzer pin as output */
    IODIR0 |= BUZZER;

    /* Initialize peripherals */
    InitUART0();
    InitLCD();
    InitKPM();
    Init_SPI();

    /* Enable external interrupt */
    Enable_EINT3();

    /* Wait for system stabilization */
    delay_s(2);

    while(1)
    {
        /* Check touch screen connection */
        if(r_flag)
        {
            CmdLCD(0x01);
            CmdLCD(0x80);

            if(str[0])
            {
                StrLCD("TOUCH CONNECTED");
                delay_s(1);
            }
        }
        else
        {
            StrLCD("TOUCH NOT CONNECTED");
            delay_s(1);
        }

        /* Get password from user */
        GetPassword();

        /* Read stored password from EEPROM */
        EEPROM_Read_String(stored_pass);

        while(1)
        {
            /* Read entered password */
            ReadPassword();

            /* Validate password */
            if(ValidatePassword())
            {
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("CORRECT PASSWORD");

                delay_ms(500);

                /* Display menu options */
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("TOUCH SCREEN:EN/DIS");

                CmdLCD(0xC0);
                StrLCD("DEVICE1:ON/OFF");

                CmdLCD(0x94);
                StrLCD("DEVICE2:ON/OFF");

                CmdLCD(0xD4);
                StrLCD("DEVICE3:ON/OFF");

                while(1)
                {
                    /* Check for touch input */
                    if(r_flag)
                    {
                        delay_s(1);
                        r_flag = 0;

                        /* Extract X coordinate */
                        for(k=0,j=4;j<7;j++,k++)
                            x[k]=str[j];
                        x[k]='\0';

                        /* Extract Y coordinate */
                        for(k=0,j=11;j<14;j++,k++)
                            y[k]=str[j];
                        y[k]='\0';

                        /* Extract Z coordinate */
                        for(k=0,j=18;j<21;j++,k++)
                            z[k]=str[j];
                        z[k]='\0';

                        /* Convert strings to integers */
                        a=atoi(x);
                        b=atoi(y);
                        c=atoi(z);

                        /* Touch screen enable/disable area */
                        if((a>=50&&a<=150)&&(b>=50&&b<=150)&&(c>=30&&c<=120))
                        {
                            touchenable ^= 1;

                            if(touchenable)
                            {
                                CmdLCD(0x80);
                                StrLCD("TOUCH SCREEN:EN     ");
                            }
                            else
                            {
                                CmdLCD(0x80);
                                StrLCD("TOUCH SCREEN:DIS    ");

                                /* Disable all devices */
                                disable();
                            }
                        }

                        /* Execute device controls only when touch is enabled */
                        if(touchenable)
                        {
                            /* Device 1 touch area */
                            if((a>=20&&a<=40)&&(b>=150&&b<=200)&&(c>=10&&c<=30))
                            {
                                device1();
                            }

                            /* Device 2 touch area */
                            if((a>=20&&a<=70)&&(b>=20&&b<=70)&&(c>=10&&c<=70))
                            {
                                device2();
                            }

                            /* Device 3 touch area */
                            if((a>=170&&a<=220)&&(b>=150&&b<=220)&&(c>=50&&c<=100))
                            {
                                device3();
                            }

                            /* Clear buffers */
                            memset(str,'\0',25);
                            memset(x,'\0',10);
                            memset(y,'\0',10);
                            memset(z,'\0',10);

                            a=b=c=0;
                        }
                    }
                }
            }
            else
            {
                /* Wrong password entered */
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("WRONG PASSWORD");

                delay_s(1);

                break;
            }
        }
    }
}