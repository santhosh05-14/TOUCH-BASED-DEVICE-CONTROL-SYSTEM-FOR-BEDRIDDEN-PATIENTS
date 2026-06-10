/* Header file for LCD function declarations */

#include "types.h"

/* Function to write data/command to LCD */
void WriteLCD(u8 data);

/* Function to send command to LCD */
void CmdLCD(u8 cmd);

/* Function to display a character on LCD */
void CharLCD(u8 ascii);

/* Function to initialize LCD */
void InitLCD(void);

/* Function to display a string on LCD */
void StrLCD(u8 *str);

/* Function to display unsigned integer on LCD */
void U32LCD(u32 n);

/* Function to display signed integer on LCD */
void S32LCD(s32 n);

/* Function to display binary number on LCD */
void BinLCD(u32 n, u8 nbd);

/* Function to create custom characters in CGRAM */
void BuildCGRAM(u8 *p, u8 nBytes);

/* Function to display floating point number on LCD */
void f32LCD(f32 fnum, u8 ndp);

/* Function to display octal number on LCD */
void OctLCD(u32 n);

/* Function to display hexadecimal number on LCD */
void HexLCD(u32 n);