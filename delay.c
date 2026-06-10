/* Delay in microseconds */
void delay_us(unsigned int tdly)
{
    /* Adjust count for 1 microsecond delay */
    tdly *= 12;

    /* Generate delay */
    while(tdly--);
}

/* Delay in milliseconds */
void delay_ms(unsigned int tdly)
{
    /* Adjust count for 1 millisecond delay */
    tdly *= 12000;

    /* Generate delay */
    while(tdly--);
}

/* Delay in seconds */
void delay_s(unsigned int tdly)
{
    /* Adjust count for 1 second delay */
    tdly *= 12000000;

    /* Generate delay */
    while(tdly--);
}
