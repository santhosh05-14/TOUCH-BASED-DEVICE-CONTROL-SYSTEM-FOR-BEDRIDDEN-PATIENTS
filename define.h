/* Set the bit at position BP in WORD*/
#define SETBIT(WORD,BP) (WORD|=(1<<BP))

/* Clear the bit at position BP in WORD*/    
#define CLRBIT(WORD,BP) (WORD&=~(1<<BP))

/* Read the status of bit at position BP (returns 0 or 1) */ 
#define STATUSBIT(WORD,BP) ((WORD>>BP)&1)

/*Write BIT value (0 or 1) to bit position BP*/   
#define WRITEBIT(WORD,BP,BIT) (WORD=(WORD&~(1<<BP))|(BIT<<BP))            

/* Write a 4-bit nibble at starting bit position SBP*/
#define WRITENIBBLE(WORD,SBP,NIBBLE) (WORD=(WORD&~(15<<SBP))|(NIBBLE<<SBP))

/*Write an 8-bit byte at starting bit position SBP*/           
#define WRITEBYTE(WORD,SBP,BYTE) ((WORD=(WORD&~(255<<SBP))|(BYTE<<SBP)))

/*Write a 16-bit half-word at starting bit position SBP*/
#define WRITEHW(WORD,SBP,HW) ((WORD=(WORD&(0XFFFF<<SBP))|(HW<<SBP)))

/*Set only the specified bit and clear all other bits*/
#define SSETBIT(WORD,BP) (WORD=(1<<BP))

/*clear only the specified bit and set all other bits*/
#define SCLRBIT(WORD,BP) (WORD=~(1<<BP))

/*Read a 4-bit nibble from bit position BP*/
#define READNIBBLE(WORD,BP) (WORD=((WORD>>BP)&15))

/*Buzzer connected to P0.21*/
#define BUZZER (1<<21)

/*LED1 connected to P0.24*/
#define LED1 (1<<24)

/*LED1 connected to P0.25*/
#define LED2 (1<<25)