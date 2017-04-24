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
#include "power.h"
#include "sleepmgr.h"
#include "conf_qs_tc_timer.h"
#include "asf.h"


#define CONF_TC_MODULE TC3

void configure_tc(void);
void configure_tc_callbacks(void);
void tc_callback_to_toggle_led(
		struct tc_module *const module_inst);
void go_to_sleep(struct tc_module *const module_inst);



//! [module_inst]
struct tc_module tc_instance;
struct adc_module adc_instance;
struct dac_module dac_instance;
struct usart_module usart_instance;
struct spi_module spi_instance;



 void delay (uint16_t length)
 {
	 // Simple delay loop
	 for (uint16_t i=0; i<length; i++) {
		 for (uint8_t j=0; j<255; j++) {
			 asm volatile("nop");
		 }
	 }
 }

/*
Funktion som ska läsa av temperatur. Just nu togglas lampan
beroende på periods tiden och vad channel 0 ska trigga på 

*/
void tc_callback_to_toggle_led(
		struct tc_module *const module_inst)
{	
	/*
	port_pin_set_output_level(LED_0_PIN,LED_0_ACTIVE);
	delay(500);
	port_pin_set_output_level(LED_0_PIN,LED_0_INACTIVE);
	*/
	port_pin_toggle_output_level(LED_0_PIN);
}



void tc_sleep(struct tc_module *const module_inst){
system_sleep();
}




//! [setup]
void configure_tc(void)
{
	//! [setup_config]
	struct tc_config config_tc;

	//! [setup_config_defaults]
	tc_get_config_defaults(&config_tc);


	//! [setup_change_config]
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_8_bit.period = 100;
	config_tc.counter_8_bit.compare_capture_channel[0] = 20;


	//! [setup_set_config]
	tc_init(&tc_instance, TC3, &config_tc);


	//! [setup_enable]
	tc_enable(&tc_instance);

}

void configure_tc_callbacks(void)
{
	//! [setup_register_callback]
	tc_register_callback(&tc_instance, tc_sleep,
			TC_CALLBACK_OVERFLOW);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
			TC_CALLBACK_CC_CHANNEL0);


	//! [setup_enable_callback]
	//tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);

}
//! [setup]

int main(void)
{
	
	system_init();
	
//! [setup_init]
	configure_tc();
	
	configure_tc_callbacks();
	

	system_switch_performance_level(PM_PLCFG_PLSEL_PL0_Val);
	system_performance_level_enable();
	
	system_interrupt_enable_global();
	

	//! [main_loop]
	while (true) {
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();
	}
}