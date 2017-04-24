/*
 * Calculations_For_AVR.c
 *
 * Created: 2017-04-03 10:42:31
 * Author : Patricia
 */ 

#include <avr/io.h>
#include <a>
#include "asf.h"
#include "led.h"
#include "delay.h"
#include "sysclk.h"



int main(void)
{
sysclk_init();
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



