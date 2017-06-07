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
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
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

#include "avr/io.h"
#include "avr/interrupt.h"
#include "delay.h"
#include "avr/power.h"
#include "sleep.h"

uint16_t adc_results=0;


void disable_peripherals(void){
	PR.PRGEN= PR_USB_bm | PR_AES_bm  | PR_RTC_bm | PR_EVSYS_bm | PR_DMA_bm;
	PR.PRPA=PR_DAC_bm | PR_AC_bm;
	PR.PRPB=PR_DAC_bm | PR_AC_bm;

	PR.PRPC=PR_TWI_bm | PR_USART1_bm | PR_USART0_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC1_bm | PR_TC0_bm;
	PR.PRPD=PR_TWI_bm | PR_USART1_bm | PR_USART0_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC1_bm | PR_TC0_bm;
	PR.PRPE=PR_TWI_bm | PR_USART1_bm | PR_USART0_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC1_bm | PR_TC0_bm;
	PR.PRPF=PR_TWI_bm | PR_USART1_bm | PR_USART0_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC1_bm | PR_TC0_bm;

}


void ADC_init(void){
CCP = 0xD8;
CLK.PSCTRL = CLK_PSADIV_2_gc;
ADCA.CTRLB = ADC_CURRLIMIT_HIGH_gc;
ADCA.REFCTRL = ADC_REFSEL_INTVCC_gc;
ADCA.PRESCALER = ADC_PRESCALER_DIV4_gc;
ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN0_gc;
ADCA.CH0.INTCTRL = ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_HI_gc;
ADCA.CTRLA = ADC_ENABLE_bm;

}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	


	sysclk_init();
	board_init();
	//ioport_set_pin_dir(LED0_GPIO,IOPORT_DIR_OUTPUT);
	
	#if (BOARD == XMEGA_A3BU_XPLAINED)
	/* The status LED must be used as LED2, so we turn off
	 * the green led which is in the same packaging. */
	ioport_set_pin_high(LED3_GPIO);
#endif

/*
set_sleep_mode(SLEEP_MODE_PWR_SAVE);
sleep_enable();
sleep_cpu();
*/
	ADC_init();
	
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
	ADCA.CH0.CTRL = ADC_CH_START_bm;
	PMIC.CTRL = PMIC_HILVLEN_bm;
	sei();
	while (1)
	{
	sleep_cpu();


	}
	

	/* Insert application code here, after the board has been initialized. */
}

ISR (ADCA_CH0_vect){
	//ADC results
	adc_results = ADCA_CH0RES;
	ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm;
	//start conversion from ADC channel 0
	ADCA.CH0.CTRL = ADC_CH_START_bm;
	ioport_toggle_pin(LED0_GPIO);
}