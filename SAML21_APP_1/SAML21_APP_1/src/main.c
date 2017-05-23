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
#include "delay.h"
#include "conf_qs_tc_timer.h"

void configure_tc(void);
void configure_adc(void);
void configure_tc_callbacks(void);
void tc_callback_to_toggle_led(
struct tc_module *const module_inst);


// module_inst
struct tc_module tc_instance;
struct adc_module adc_instance;




void tc_callback_to_toggle_led(
struct tc_module *const module_inst)
{
	//port_pin_toggle_output_level(LED0_PIN);
	//delay(10);
	adc_start_conversion(&adc_instance);
	uint16_t result;
	adc_read(&adc_instance, &result);
	//delay(50);
	//port_pin_toggle_output_level(LED0_PIN);
}


//! [setup]
void configure_tc(void)
{
	//setup_config
	struct tc_config config_tc;
	//setup_config_defaults
	tc_get_config_defaults(&config_tc);

	//setup_change_config
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_source = GCLK_GENERATOR_0;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_8_bit.period = 255;
	config_tc.counter_8_bit.compare_capture_channel[0] = 50;

	//setup_set_config
	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);
	
	//setup_enable
	tc_enable(&tc_instance);
}

void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}

void configure_tc_callbacks(void)
{
	//! [setup_register_callback]
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_CC_CHANNEL0);


	//setup_enable_callback
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);

}

int main(void)
{
	system_init();

	//setup_init
	configure_tc();
	configure_adc();
	configure_tc_callbacks();

	//enable_global_interrupts
	system_interrupt_enable_global();

	//set sleep mode
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	port_pin_set_output_level(LED0_PIN,LED_0_INACTIVE);
	

	//until interrupt sleep
	while (true) {
		system_sleep();
	}
}
