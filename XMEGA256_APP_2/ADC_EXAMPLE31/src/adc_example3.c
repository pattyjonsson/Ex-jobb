/**
 * \file
 *
 * \brief AVR XMEGA Analog to Digital Converter Driver Example 3
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \mainpage
 *
 * \section intro Introduction
 * This simple example shows how to use the new scan feature found in the
 * XMEGA-...U devices.
 *
 * \section files Main files:
 * - adc_example3.c: ADC driver example application
 * - conf_adc.h: configuration of the ADC driver
 *
 * \section apiinfo ADC driver API
 * The ADC driver API can be found \ref adc_group "here".
 *
 * \section deviceinfo Device Info
 * All AVR XMEGA U devices with an ADC can be used or devices that have the
 * scan register on ADCA channel 0.
 *
 * \section exampledescription Description of the example
 * ADC A is configured for signed, 12-bit conversions using the internal 1 V
 * voltage reference. The conversions are configured to be triggered from the
 * event system. Channel 0 of the ADC is configured for differential measurement
 * of all ADCA pins (PA0-PA7) with internal ground.
 *
 * An ADC interrupt callback function is used to handle the conversion results,
 * each result is stored into an array at the position corresponding to the pin
 * number, e.g. PA0 result is stored in adc_scan_results[0].
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <string.h>

static volatile uint16_t adc_scan_results[1000];

//volatile uint8_t adc_results = 100;
volatile uint16_t counter=0;
volatile uint32_t adc_results = 0;




/************************************************************************/
/* Lowers power consumption                                                                     */
/************************************************************************/
void disable_JTAG(void){
	CCP = CCP_IOREG_gc;
	MCU.MCUCR=MCU_JTAGD_bm;

}
/************************************************************************/
/*         Disable unused peripherals to save power                                                             */
/************************************************************************/
void disable_peripherals(void){
	PR.PRGEN=PR_USB_bm | PR_AES_bm  | PR_EVSYS_bm | PR_DMA_bm;

	PR.PRPA=PR_DAC_bm | PR_AC_bm;
	PR.PRPB=PR_DAC_bm | PR_AC_bm;

	PR.PRPC= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC0_bm | PR_TC1_bm;
	PR.PRPD= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC0_bm | PR_TC1_bm;
	PR.PRPE= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC0_bm | PR_TC1_bm;
	PR.PRPF= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC0_bm | PR_TC1_bm;
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

/**
 * \brief ADC Example 3 main application function
 */
int main(void)
{
	board_init();
	disable_peripherals();
	disable_JTAG();
	ADC_init();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
	ADCA.CH0.CTRL = ADC_CH_START_bm;
	PMIC.CTRL = PMIC_HILVLEN_bm;
	sei();

	 while (1){
		sleep_cpu();
	 }
}

ISR(ADCA_CH0_vect){
	adc_results = ADCA_CH0RES;
	ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm;
	ADCA.CH0.CTRL = ADC_CH_START_bm;
	adc_scan_results[counter]=adc_results;
	counter++;
	if(counter==1000){
		int sum=0;
		for(int i = 0; i<counter; i++){
			sum = sum + adc_scan_results[i];
		}
		counter=0;
		uint16_t send_value=sum/1000;
		
	}
}
