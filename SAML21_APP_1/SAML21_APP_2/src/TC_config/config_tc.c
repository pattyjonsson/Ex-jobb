/*
 * config_tc.c
 *
 * Created: 2017-06-14 13:54:27
 *  Author: Patricia
 */ 
#include "asf.h"
 #include "TC_config/config_tc.h"
 #include "ADC/configure_adc.h"

 uint32_t sum = 0;
 uint16_t counter = 0;

 /************************************************************/
 /* Interrupt function that reads from the ADC and adds	     */
 /*  them up. After 1000 reads they are divided by 1000.	 */						 
 /************************************************************/
 void tc_callback(
 struct tc_module *const module_inst)
 {
	
	if(counter==0){
		port_pin_set_output_level(PIN_PB05,1);
	}
	counter++;
	uint16_t result;
	uint32_t outvalue;
	
	adc_start_conversion(&adc_instance);
	adc_read(&adc_instance, &result);
	sum= sum + result;

	if(counter==1000){
		outvalue=sum/1000;
		counter=0;
		port_pin_set_output_level(PIN_PB05,0);
	}
 }

 /************************************************************/
 /*	TC-timer interrupt every 10 ms							 */
 /************************************************************/
 void configure_tc(void)
 {
	 struct tc_config config_tc;
	 tc_get_config_defaults(&config_tc);
	 config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	 config_tc.clock_source = GCLK_GENERATOR_0;
	 config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV256;
	 config_tc.counter_8_bit.period = 159;
	 config_tc.counter_8_bit.compare_capture_channel[0] = 1;	
	 tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);
	 tc_enable(&tc_instance);
	

 }

 /************************************************************/
 /*	Enable callbacks										 */
 /************************************************************/
 void configure_tc_callbacks(void)
 {
	 tc_register_callback(&tc_instance, tc_callback,
	 TC_CALLBACK_CC_CHANNEL0);
	 tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
 }