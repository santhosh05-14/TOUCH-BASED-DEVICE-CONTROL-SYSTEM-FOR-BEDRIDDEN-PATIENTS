/* External Interrupt 3 Interrupt Service Routine */
void eint3_isr(void)__irq;

/* Function to enable and configure EINT3 */
void Enable_EINT3(void);

/* UART0 Interrupt Service Routine */
void UART0_isr(void) __irq;

/* Function to initialize UART0 */
void InitUART0(void);