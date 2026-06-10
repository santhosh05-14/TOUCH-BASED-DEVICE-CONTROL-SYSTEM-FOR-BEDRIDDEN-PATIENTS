/* Header file for password management function declarations */

/* Function to read password from EEPROM */
void ReadPassword(void);

/* Function to get password from keypad */
void GetPassword(void);

/* Function to validate entered password */
u8 ValidatePassword(void);

/* Function to store default password in EEPROM */
void StorePassword(void);

/* Function to read password string from EEPROM */
void EEPROM_Read_String(u8 *p);

/* Function to write updated password into EEPROM */
void EEPROM_Write_String(u8 *p);