/* lcd_defines.h */

/* LCD Pin Definitions */

/* LCD data pins connected from P0.8 to P0.15 */
#define LCD_DATA 8

/* Register Select pin connected to P0.16 */
#define RS 16

/* Enable pin connected to P0.17 */
#define EN 17

/* Read/Write pin connected to P0.18 */
#define RW 18


/* LCD Command Definitions */

/* Clear LCD display */
#define CLEAR_LCD 0x01

/* Return cursor to home position */
#define RET_CUR_HOME 0x02

/* Configure LCD in 4-bit mode, 1-line display */
#define MODE_4BIT_1LINE 0x20

/* Configure LCD in 4-bit mode, 2-line display */
#define MODE_4BIT_2LINE 0x28

/* Configure LCD in 8-bit mode, 1-line display */
#define MODE_8BIT_1LINE 0x30

/* Configure LCD in 8-bit mode, 2-line display */
#define MODE_8BIT_2LINE 0x38

/* Turn display OFF */
#define DISP_OFF 0x08

/* Turn display ON, cursor OFF */
#define DISP_ON_CUR_OFF 0x0C

/* Turn display ON, cursor ON */
#define DISP_ON_CUR_ON 0x0E

/* Turn display ON, cursor blinking */
#define DISP_ON_CUR_BLINK 0x0F

/* Move cursor to first line, first position */
#define GOTO_LINE1_POS0 0x80

/* Move cursor to second line, first position */
#define GOTO_LINE2_POS0 0xC0

/* Select CGRAM for custom character creation */
#define GOTO_CGRAM 0x40

/* Automatically shift cursor to the right */
#define SHIFT_CUR_RIGHT 0x06