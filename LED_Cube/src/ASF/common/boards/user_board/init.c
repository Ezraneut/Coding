/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
    /* This function is meant to contain board-specific initialization code
     * for, e.g., the I/O pins. The initialization can rely on application-
     * specific board configuration, found in conf_board.h.
     */
	ioport_configure_pin(SHIFT_DS_1, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(SHIFT_SHCP_1, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(SHIFT_STCP_1, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	
	ioport_configure_pin(SHIFT_DS_2, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(SHIFT_SHCP_2, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(SHIFT_STCP_2, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	
	ioport_configure_pin(CUBE_LVL_1, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(CUBE_LVL_2, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(CUBE_LVL_3, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);
	ioport_configure_pin(CUBE_LVL_4, IOPORT_DIR_OUTPUT | IOPORT_INIT_LOW);	
}
