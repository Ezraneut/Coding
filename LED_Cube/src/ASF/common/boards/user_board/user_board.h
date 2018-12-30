/**
 * \file
 *
 * \brief User board definition template
 *
 */

/* This file is intended to contain definitions and configuration details for
* features and devices that are available on the board, e.g., frequency and
* startup time for an external crystal, external memory devices, LED and USART
* pins.
*/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>

#define SHIFT_DS_1		IOPORT_CREATE_PIN(PORTC, 0U)	//SER4
#define SHIFT_SHCP_1 	IOPORT_CREATE_PIN(PORTC, 2U)	//SRCLK
#define SHIFT_STCP_1 	IOPORT_CREATE_PIN(PORTC, 1U)	//RCLK
#define SHIFT_PORT_1 	PORTC

#define SHIFT_DS_2 		IOPORT_CREATE_PIN(PORTC, 3U)	//SER
#define SHIFT_SHCP_2 	IOPORT_CREATE_PIN(PORTC, 5U)	//SRCLK
#define SHIFT_STCP_2 	IOPORT_CREATE_PIN(PORTC, 4U)	//RCLK
#define SHIFT_PORT_2	PORTC

#define CUBE_LVL_1 		IOPORT_CREATE_PIN(PORTD, 0U)
#define CUBE_LVL_2 		IOPORT_CREATE_PIN(PORTD, 1U)
#define CUBE_LVL_3 		IOPORT_CREATE_PIN(PORTD, 2U)
#define CUBE_LVL_4 		IOPORT_CREATE_PIN(PORTD, 3U)
#define CUBE_LYR_PORT	PORTD

// External oscillator settings.
// Uncomment and set correct values if external oscillator is used.

// External oscillator frequency
//#define BOARD_XOSC_HZ          8000000

// External oscillator type.
//!< External clock signal
//#define BOARD_XOSC_TYPE        XOSC_TYPE_EXTERNAL
//!< 32.768 kHz resonator on TOSC
//#define BOARD_XOSC_TYPE        XOSC_TYPE_32KHZ
//!< 0.4 to 16 MHz resonator on XTALS
//#define BOARD_XOSC_TYPE        XOSC_TYPE_XTAL

// External oscillator startup time
//#define BOARD_XOSC_STARTUP_US  500000


#endif // USER_BOARD_H
