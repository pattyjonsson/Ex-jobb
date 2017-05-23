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
#include "DelayFunctions.h"
#include "initDA.h"
#include "ISR_Handler.h"
#include "interupttimer.h"

int main (void)
{
	/*Initialize the Arduino Due system*/
	sysclk_init();
	board_init();
	inializeconfig_tc();

	delayInit();
	daccInit();

	while(1)	/* repeat blink to infinity */
	{
		 /* sets a bit of I/O port B to high */
			gpio_toggle_pin(LED1_GPIO);

		delayMicroseconds(500000);
		 /* clears a bit of I/O port B */
			gpio_toggle_pin(LED1_GPIO);

		delayMicroseconds(500000);
	}
}