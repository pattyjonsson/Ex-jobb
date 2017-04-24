/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "delay.h"

int main(void)
{
	//sysclk_init();
	board_init();
	ioport_init();

	/* Set output direction on the given LED IOPORTs */
	ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);

	/* Set direction and pullup on the given button IOPORT */


	while (true) {
		/* Get value from button and output it on led */
		ioport_set_pin_level(LED0_GPIO,1);
		delay(5000);
		ioport_set_pin_level(LED0_GPIO,0);
		
	}
}
