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
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
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
#include "TC_config/config_tc.h"
#include "ADC/configure_adc.h"




int main(void)
{

	system_init();
	configure_adc();
	configure_tc();
	configure_tc_callbacks();
	
	ioport_set_pin_dir(PIN_PB05,IOPORT_DIR_OUTPUT);
	system_interrupt_enable_global();

	
	system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE); 
	while (true) {
		system_sleep();
		
	}

}
