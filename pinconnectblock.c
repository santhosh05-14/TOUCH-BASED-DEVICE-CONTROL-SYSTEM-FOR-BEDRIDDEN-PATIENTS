/* Include LPC21xx header file */
#include <LPC21XX.h>

/* Function to configure pin function using PINSEL registers */
void cfgportpinfunc(int portno, int pinno, int fn)
{
    /* Check for Port 0 */
    if(portno == 0)
    {
        /* Pins P0.0 to P0.15 use PINSEL0 */
        if(pinno < 16)
        {
            PINSEL0 = ((PINSEL0 & ~(3 << (pinno * 2))) |
                      (fn << (pinno * 2)));
        }
        /* Pins P0.16 to P0.31 use PINSEL1 */
        else
        {
            PINSEL1 = ((PINSEL1 & ~(3 << ((pinno - 16) * 2))) |
                      (fn << ((pinno - 16) * 2)));
        }
    }
    else
    {
        /* No configuration required for other ports */
    }
}