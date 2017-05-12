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


struct adc_module adc_instance;void configure_adc(void);
void read_adc(void);

uint16_t adc_value[1000];
void configure_adc(void)
{
	 struct adc_config conf_adc;

	 adc_get_config_defaults(&conf_adc);

	 conf_adc.clock_source = GCLK_GENERATOR_1;
	 conf_adc.reference = ADC_REFERENCE_INTVCC1;
	 conf_adc.clock_prescaler = ADC_CTRLB_PRESCALER_DIV16;
	// conf_adc.differential_mode = true;
	// conf_adc.positive_input = ADC_POSITIVE_INPUT_PIN0;
	// conf_adc.negative_input = ADC_NEGATIVE_INPUT_PIN4;

	 adc_init(&adc_instance, ADC, &conf_adc);

	 adc_enable(&adc_instance);	 delay(50);
}
//volatile uint16_t r;void read_adc(void){	//
	adc_start_conversion(&adc_instance);
	uint16_t result=0;	for(int i=0; i<1000; i++){		//delay(50);		adc_read(&adc_instance, &result);		//delay(50);		//r=result;		adc_value[i]=result;			}}

int main (void)
{
	system_init();

	configure_adc();
	

	system_interrupt_enable_global();

	

	while (1) {
	read_adc();
	//delay(5000);
	}
}
