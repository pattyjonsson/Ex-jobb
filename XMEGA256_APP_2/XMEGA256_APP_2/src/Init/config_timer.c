/*
 * config_timer.c
 *
 * Created: 2017-06-13 14:42:32
 *  Author: Patricia
 */ 

 #include "config_timer.h"

 uint32_t sum=0;
 uint16_t counter=0;



 /************************************************************************/
 /* Interrupt function that reads from the ADC and adds					  /
 /*  them up. After 1000 reads they are divided by 1000.				  /
 /************************************************************************/
 static void example_cca_interrupt_callback(void)
 {
	adc_start_conversion(&ADCA, ADC_CH0);
	/*First read set the pin high*/
	 if(counter==0) {
		ioport_toggle_pin(J1_PIN1);
	 }
	 uint32_t invalue, outvalue;
	 counter++; 
	 invalue = ADCA_CH0RES;
	 /*Add up the values*/
	 sum = sum + invalue;
	 /*When 1000 values divide sum by 1000, restart counter and set pin low */
	 if(counter==1000){
		outvalue=sum/1000;
		counter=0;
		ioport_toggle_pin(J1_PIN1);
	 }	  
 }
 /************************************************************************/
 /* Setting up the timer to do interrupts every 10 ms                    */
 /************************************************************************/
 void config_timer(){
	tc_enable(&TIMER_EXAMPLE);
	tc_set_cca_interrupt_callback(&TIMER_EXAMPLE,
			example_cca_interrupt_callback);
	tc_set_wgm(&TIMER_EXAMPLE, TC_WG_NORMAL);	
	tc_write_period(&TIMER_EXAMPLE, TIMER_EXAMPLE_PERIOD);
	tc_write_cc(&TIMER_EXAMPLE, TC_CCA, TIMER_EXAMPLE_PERIOD);
	tc_enable_cc_channels(&TIMER_EXAMPLE,(enum tc_cc_channel_mask_enable_t)(TC_CCAEN));
	tc_set_cca_interrupt_level(&TIMER_EXAMPLE, TC_INT_LVL_LO);
	tc_set_resolution(&TIMER_EXAMPLE, 31250);
}

