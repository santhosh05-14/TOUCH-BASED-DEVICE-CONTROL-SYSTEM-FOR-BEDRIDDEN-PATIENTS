/* SPI Pin Definitions */

/* Serial Clock (SCK) connected to P0.4 */
#define SCLK 4

/* Master In Slave Out (MISO) connected to P0.5 */
#define MISO 5

/* Master Out Slave In (MOSI) connected to P0.6 */
#define MOSI 6

/* Chip Select (CS) connected to P0.7 */
#define CS 7


/* SPI Clock Configuration */

/* Oscillator Frequency */
#define FOSC 12000000

/* CPU Clock Frequency */
#define CCLK (FOSC * 5)

/* Peripheral Clock Frequency */
#define PCLK (CCLK / 4)

/* Required SPI Communication Speed */
#define SPI_SPEED 100000

/* SPI Clock Divider Value */
#define LOADVAL (PCLK / SPI_SPEED)


/* SPI Control Register Bit Definitions */

/* Clock Phase Bit Position */
#define CPHA 3

/* Clock Polarity Bit Position */
#define CPOL 4

/* Master Mode Select Bit Position */
#define MSTR 5

/* SPI Transfer Complete Flag Bit Position */
#define SPIF 7


/* EEPROM Command Definitions */

/* EEPROM Write Command */
#define WRITE 0x02

/* EEPROM Write Enable Command */
#define WREN 0x06

/* EEPROM Write Disable Command */
#define WRDI 0x04

/* EEPROM Read Command */
#define READ 0x03