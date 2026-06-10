/* Header file for keypad function declarations */

#include "types.h"

/* Function to initialize keypad */
void InitKPM(void);

/* Function to scan keypad columns */
u8 ColScan(void);

/* Function to identify active row */
u8 RowCheck(void);

/* Function to identify active column */
u8 ColCheck(void);

/* Function to scan and return pressed key value */
u8 KeyScan(void);

/* Function to read a multi-digit number from keypad */
u32 ReadNum(void);