/**
 * \file
 *
 * \brief AVR XMEGA TC Driver Example 1
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
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
 * This simple example shows how to use the \ref tc_group to toggle LEDs.
 *
 * \section files Main files:
 *  - tc.c Timer XMEGA Timer Counter driver implementation
 *  - tc.h Timer XMEGA Timer Counter driver definitions
 *  - tc_example1.c example application
 *  - conf_example.h: configuration of the example
 *
 * \section driverinfo TC Driver
 * The XMEGA TC driver can be found \ref tc_group "here".
 *
 * \section deviceinfo Device Info
 * All AVR XMEGA devices with an tc can be used.
 *
 * \section exampledescription Description of the example
 * The example will configure one TC module (\ref TIMER_EXAMPLE) in normal mode and
 * use three TC interrupts (overflow, Capture/Compare Channels A and B).
 *
 * The TC is setup to use a 31250Hz resolution clock and a 31250 period value
 * resulting in a 1Hz TC overflow frequency.
 * Compare Channels A and B will be setup at 1/4 and 1/2 of the TC period.

 * Each callback interrupts functions are setup to toggle a LED.
 *  - LED0: Toggles on TC overflow interrupt
 *  - LED1: Toggle on Compare Channel A
 * In the case of A1 Xplain:
 *  - LED2: Toggle on Compare Channel B interrupts
 * In the case of A3BU Xplained:
 *  - Status LED: Toggles red on Compare Channel B interrupts
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
#include <conf_example.h>
#include <string.h>
#include <asf.h>
#include "avr/power.h"
#include "avr/sleep.h"

volatile uint16_t adc_results=0;
volatile uint16_t re=0;
volatile uint8_t deep_sleep = 0;


/************************************************************************/
/* Initialize  ADC                                                                     */
/************************************************************************/

void ADC_init(void){
CCP=0xD8;
CLK.PSCTRL=CLK_PSADIV_2_gc;
ADCA.CTRLB=ADC_CURRLIMIT_HIGH_gc;
ADCA.REFCTRL=ADC_REFSEL_INTVCC_gc;
ADCA.PRESCALER=ADC_PRESCALER_DIV4_gc;
ADCA.CH0.CTRL= ADC_CH_INPUTMODE_SINGLEENDED_gc;
ADCA.CH0.MUXCTRL=ADC_CH_MUXPOS_PIN0_gc;
ADCA.CH0.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_HI_gc;
ADCA.CTRLA=ADC_ENABLE_bm;
}



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

static void alarm(uint32_t time){

rtc_set_alarm_relative(2);
ADCA.CH0.CTRL = ADC_CH_START_bm;
adc_results = ADCA_CH0RES;
//gpio_toggle_pin(LED0_GPIO);


}


int main(void)
{
	pmic_init();
	board_init();
	sysclk_init();
	disable_JTAG();
	disable_peripherals();
	ADC_init();

	adc_enable(&ADCA);

	rtc_init();
	rtc_set_callback(alarm);
		
	cpu_irq_enable();
	sleep_enable();
	rtc_set_alarm_relative(3);
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	while(1){
	
	sleep_cpu();
	
	
	//PMIC.CTRL = PMIC_HILVLEN_bm;
	
	
	}
}
