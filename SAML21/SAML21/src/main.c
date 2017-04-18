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
#include "interrupt.h"
#include "clock.h"
#include "tc.h"
#include "tc_interrupt.h"
#include "conf_clocks.h"
#include "complex.h"



#define CONF_TC_MODULE TC3

struct tc_module tc_instance;
static void TCC0_Init(void);
void delay(uint16_t);
void tc_callback_to_toggle_led(struct tc_module *const );
void configure_tc(void);
void configure_tc_callbacks(void);


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
ISR (TIMER0_OVF_vect){
	if(port_pin_get_output_level(LED_0_PIN)){
		port_pin_set_output_level(LED_0_PIN,!LED_0_ACTIVE);
		
	}else{
		port_pin_set_output_level(LED_0_PIN,LED_0_ACTIVE);
	}

}
*/

void tc_callback_to_toggle_led(
struct tc_module *const module_inst)
{
	//port_pin_toggle_output_level(LED_0_PIN);
		if(port_pin_get_output_level(LED_0_PIN)){
			port_pin_set_output_level(LED_0_PIN,!LED_0_ACTIVE);
			
			}else{
			port_pin_set_output_level(LED_0_PIN,LED_0_ACTIVE);
		}
}

void configure_tc(void)
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV64;
	config_tc.counter_8_bit.period = 100;
	config_tc.counter_8_bit.compare_capture_channel[0] = 50;
	config_tc.counter_8_bit.compare_capture_channel[1] = 54;
	tc_init(&tc_instance, TC0, &config_tc);
	tc_enable(&tc_instance);
}
void configure_tc_callbacks(void)
{
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_OVERFLOW);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_CC_CHANNEL0);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_CC_CHANNEL1);
	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL1);
}



static void TCC0_Init(void){
	// - Enable TCC0 Bus clock (Timer counter control clock)
	MCLK->APBCMASK.reg |= MCLK_APBCMASK_TCC0;
	//Enable GCLK for TCC0 and link it to GCLK0 see "PCHCTRLm Mapping" from product datasheet
	GCLK->PCHCTRL[25].reg = (GCLK_PCHCTRL_CHEN|GCLK_PCHCTRL_GEN(0));
	// - Disable TCC0
	TCC0->CTRLA.reg &=~(TCC_CTRLA_ENABLE);
	// - Set TCC0 in waveform mode Normal PWM
	TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM;
	// - Set PER to maximum counter value (resolution : 0xFF)
	TCC0->PER.reg = 0xFF;
	// - Set WO[0] compare register to 0x7F (PWM duty cycle = 50%)
	TCC0->CC[0].reg = 0x7F;
	// - Enable Channel 0 Match Event Output
	TCC0->EVCTRL.bit.MCEO0 = 0x01;
	// - Set PB10 (LED) as TCC0 Waveform out (PMUX : F = 0x05)
	PORT->Group[1].WRCONFIG.reg = (uint32_t)(PORT_WRCONFIG_WRPINCFG|PORT_WRCONFIG_WRPMUX|1<<10|PORT_WRCONFIG_PMUXEN|(0x5<<PORT_WRCONFIG_PMUX_Pos));
	// - ENABLE TCC0
	TCC0->CTRLA.reg |= TCC_CTRLA_ENABLE;
}



int main (void)
{
	system_init();
	//TCC0_Init();
	
	//configure_tc();
	//configure_tc_callbacks();
	
	//TC_CLOCK_PRESCALER_DIV64;
	//system_interrupt_enable_global();
	while (1) {

/*	port_pin_set_output_level(LED_0_PIN,LED_0_ACTIVE);
	delay(50);
	port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
	delay(5000);
	*/



		/* Is button pressed? */
//		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
//			/* Yes, so turn LED on. */
//			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
//		} else {
//			/* No, so turn LED off. */
//			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
//		}

		
	}
}
