# Touch-Based Device Control System for Bedridden Patients

## Overview
- Enables bedridden patients to control electronic devices using a touch-based interface.
- Developed using the LPC2124 ARM7 Microcontroller.
- Provides secure access through password authentication.
- Stores user credentials in EEPROM via SPI communication.
- Allows device ON/OFF control through a touch screen.
- Displays system status and user instructions on an LCD.
- Supports password entry and modification using a keypad.
- Implements interrupt-based password update functionality.
- Demonstrates Embedded C programming, UART, SPI, EEPROM interfacing, and interrupt handling.
- Improves convenience, accessibility, and independence for physically challenged individuals.

## Block Diagram

<p align="center">
  <img src="block_diagram.png" alt="Block Diagram" width="500">
</p>


## Project Images And Videos

https://drive.google.com/drive/folders/1PEEHIhly84znwjvupmyLy4uzsm6-apf1?usp=drive_link


## Features
- Touch-based device control
- Password-protected access
- EEPROM-based password storage
- Password modification using external interrupt
- LCD display for user interaction
- Matrix keypad for password entry
- SPI communication with EEPROM
- UART communication support
- LED and buzzer control
- Interrupt-driven operation

## Hardware Requirements
- LPC2124 ARM7 Microcontroller
- Resistive Touch Screen
- 16x2 LCD Display
- 4x4 Matrix Keypad
- SPI EEPROM
- LEDs
- Buzzer
- Power Supply

## Software Requirements
- Embedded C
- Keil uVision
- Flash Magic
- Proteus (Optional for Simulation)

## Working Principle
1. User enters a valid password through the keypad.
2. Password is verified using EEPROM-stored credentials.
3. Upon successful authentication, the touch interface is enabled.
4. Users can control connected devices through predefined touch regions.
5. Password can be changed securely through an interrupt-based password update mechanism.
6. Updated passwords are stored permanently in EEPROM.

## Modules Used
- LCD Interface
- Keypad Interface
- Touch Screen Interface
- UART Communication
- SPI EEPROM Interface
- External Interrupts
- Device Control Module


## Project Structure

```text
Touch-Based-Device-Control-System/
│
├── projectmain.c
├── devices.c
├── devices.h
├── lcd.c
├── lcd.h
├── kpm.c
├── kpm.h
├── SPI.c
├── SPI.h
├── password.c
├── password.h
├── interrupt.c
├── interrupt.h
├── delay.c
├── delay.h
├── lcd_defines.h
├── SPI_defines.h
├── kpmdefines.h
├── define.h
├── pinconnectblock.c
├── pinconnectblock.h
├── types.h
│
├── block_diagram.png
│ 
└── README.md
```


## Applications
- Smart Hospital Rooms
- Patient Assistance Systems
- Home Automation
- Elderly Care Systems
- Assistive Healthcare Devices

## Future Enhancements
- Wireless device control
- IoT integration
- Mobile application support
- Voice-controlled operation
- Cloud-based monitoring

## Technologies Used
- Embedded C
- LPC2124 ARM7
- SPI Protocol
- UART Communication
- EEPROM Memory
- Interrupt Programming


## Project Outcomes

- Developed a **Touch-Based Device Control System** using Embedded C.
- Implemented **user input handling** through keypad/touch interface for device control.
- Added **secure password authentication** to prevent unauthorized access.
- Integrated **LCD display module** for real-time system messages and feedback.
- Enabled communication between multiple peripherals like **LCD, keypad, SPI, and interrupts**.
- Designed an **interrupt-driven system** to improve efficiency and responsiveness.
- Achieved modular code structure by separating functionalities into different `.c` and `.h` files.
- Ensured reliable input processing and accurate device control operations.
- Strengthened understanding of embedded system concepts such as **I/O interfacing, SPI communication, and interrupt handling**.
- Built a scalable foundation for applications like **home automation and smart control systems**.

---


## Conclusion

The **Touch-Based Device Control System** was successfully designed and implemented using Embedded C. The system provides a secure and efficient way to control devices through a keypad/touch interface with real-time feedback displayed on an LCD.

The project effectively integrates multiple embedded components such as LCD, keypad, SPI communication, and interrupt handling, ensuring smooth and reliable operation. The implementation of a password-based authentication system enhances security by restricting unauthorized access.

Overall, this project helped in gaining practical knowledge of embedded systems concepts including hardware interfacing, modular programming, and interrupt-driven design. It also demonstrates how such a system can be extended for real-world applications like home automation and smart device control systems.
