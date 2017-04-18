/*
 * ISR_Handler.c
 *
 * Created: 2017-04-17 14:37:59
 *  Author: Patricia
 */ 
#include <asf.h>
#include "asf.h"


/*
void TC0_Handler(){

	volatile uint32_t ul_dummy;
	ul_dummy = tc_get_status(TC0);
	UNUSED(ul_dummy);
	if(port_pin_get_output_level(LED_0_PIN)){
		port_pin_set_output_level(LED_0_PIN,!LED_0_ACTIVE);
		}else{
			port_pin_set_output_level(LED_0_PIN,LED_0_ACTIVE);
		}
}
*/
