/*
 * configure_adc.c
 *
 * Created: 2017-06-14 14:06:39
 *  Author: Patricia
 */ 


 #include "asf.h"
 #include "ADC/configure_adc.h"

 void configure_adc(void)
 {
	 struct adc_config config_adc;
	 adc_get_config_defaults(&config_adc);
	 adc_init(&adc_instance, ADC, &config_adc);
	 adc_enable(&adc_instance);
 }