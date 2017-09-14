/*
 * config_timer.c
 *
 * Created: 2017-06-13 14:42:32
 *  Author: Patricia
 */ 

 #include "config_timer.h"
 #include "koefficienter.h"


 /************************************************************************/
 /* Interrupt function that reads from the ADC and place them in an array /
 /* The values in the array are multiplied with values from an array from /
 /* koefficienter.h														  /
 /************************************************************************/
 static void example_cca_interrupt_callback(void)
 {
	 uint32_t invalue, outvalue;
	 ioport_toggle_pin(J1_PIN0);
	 invalue = ADCA_CH0RES;
	 adc_start_conversion(&ADCA,ADC_CH0);
	 
	 /*Make the array as big as the array with the coefficients*/
	 static float xbuff[M+1]={0};
	 
	 float sum = 0;
	 /*Move the values one step forwards*/
	 for(int k =M; k>0; k--){
		 xbuff[k]=xbuff[k-1];
	 }
	 xbuff[0]=(float)invalue;
	 /*Filter the values in the array xbuff*/
	for(int i = 0; i <= M; i++){
		sum += (xbuff[i]*b[i]);
	}
	/*The effect of the signal*/
	outvalue =  sum * sum;
	
	 ioport_toggle_pin(J1_PIN0);
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

