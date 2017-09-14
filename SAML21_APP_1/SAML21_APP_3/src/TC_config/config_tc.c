/*
 * config_tc.c
 *
 * Created: 2017-06-14 13:54:27
 *  Author: Patricia
 */ 
#include "asf.h"
 #include "TC_config/config_tc.h"
 #include "koefficienter.h"
 #include "ADC/configure_adc.h"


static float xbuff[M+1]={0};
 /************************************************************/
 /* Interrupt function that reads from the ADC and place     */
 /* them in an array. The array in multiplied with values from*/ 
 /* koefficienter.h.										 */
 /************************************************************/
 void tc_callback_FIR(
 struct tc_module *const module_inst)
 {
	 port_pin_set_output_level(PIN_PB05,1);
	 
	 	uint16_t result;
		uint32_t outvalue;
	 	adc_start_conversion(&adc_instance);
	 	adc_read(&adc_instance, &result);

	 	
	 	float sum;
		/*Moves all values one step forwards*/
	 	for (int k=M; k>0; k--){
		 	xbuff[k]=xbuff[k-1];
	 	}
	 	xbuff[0]=(float)result;
		/*Multiplies the array with the coefficients*/
	 	for (int i=0; i<=M; i++){
		 	sum +=(xbuff[i]*b[i]);
	 	}
		/*Effect of the signal*/
		outvalue = sum * sum;
		
		
		port_pin_set_output_level(PIN_PB05,0);
 }

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


 void configure_tc_callbacks(void)
 {
	 tc_register_callback(&tc_instance, tc_callback_FIR,
	 TC_CALLBACK_CC_CHANNEL0);
	 tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
 }