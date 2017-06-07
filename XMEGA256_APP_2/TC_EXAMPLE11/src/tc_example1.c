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


#define M 28



/**
 * \brief Timer Counter Capture/Compare A interrupt callback function
 *
 * This function is called when an a capture compare channel A has occurred
 * TIMER_EXAMPLE and toggles LED1.
 */
static void example_cca_interrupt_callback(void)
{
	//ioport_set_pin_high(J1_PIN0);

		uint32_t invalue, outvalue;
		invalue=4095;
		static float xbuff[M+1]={0};
		//static float b[M+1] ={0.3333, 0.3333, 0.3333};
		static float b[M+1] ={-0.005549608069591, -0.02441465590089, -0.01761803676282,   0.0075711197912,
			0.02238052877789,-0.002080458233243, -0.03175457082838,  -0.0107361469078,
			0.0418150385962,  0.03540650319123, -0.05049486292566, -0.08762995174291,
			0.05635874842652,   0.3118930052645,   0.4415904308913,   0.3118930052645,
			0.05635874842652, -0.08762995174291, -0.05049486292566,  0.03540650319123,
			0.0418150385962,  -0.0107361469078, -0.03175457082838,-0.002080458233243,
			0.02238052877789,   0.0075711197912, -0.01761803676282, -0.02441465590089,
			-0.005549608069591};
		
		float sum = 0;
		
		for(int k =M; k>0; k--){
			xbuff[k]=xbuff[k-1];
		}
		xbuff[0]=(float)invalue;
		
		for(int i = 0; i <= M; i++){
			sum += (xbuff[i]*b[i]);
		}
		outvalue=sum;
		//ioport_set_pin_low(J1_PIN0);
}



int main(void)
{
	pmic_init();
	board_init();
	sysclk_init();
	sleepmgr_init();

	cpu_irq_enable();

	ioport_set_pin_dir(J1_PIN0,IOPORT_DIR_OUTPUT);

#if (BOARD == XMEGA_A3BU_XPLAINED)
	/* The status LED must be used as LED2, so we turn off
	 * the green led which is in the same packaging. */
	ioport_set_pin_high(LED3_GPIO);
#endif

	/*
	* Unmask clock for TIMER_EXAMPLE
	*/
	tc_enable(&TIMER_EXAMPLE);

	/*
	* Configure interrupts callback functions for TIMER_EXAMPLE
	* overflow interrupt, CCA interrupt and CCB interrupt
	*/

	tc_set_cca_interrupt_callback(&TIMER_EXAMPLE,
			example_cca_interrupt_callback);


	/*
	* Configure TC in normal mode, configure period, CCA and CCB
	* Enable both CCA and CCB channels
	*/

	tc_set_wgm(&TIMER_EXAMPLE, TC_WG_NORMAL);
	tc_write_period(&TIMER_EXAMPLE, TIMER_EXAMPLE_PERIOD);
	tc_write_cc(&TIMER_EXAMPLE, TC_CCA, TIMER_EXAMPLE_PERIOD);
	tc_enable_cc_channels(&TIMER_EXAMPLE,(enum tc_cc_channel_mask_enable_t)(TC_CCAEN));

	/*
	* Enable TC interrupts (overflow, CCA and CCB)
	*/

	tc_set_cca_interrupt_level(&TIMER_EXAMPLE, TC_INT_LVL_LO);


	/*
	* Run TIMER_EXAMPLE at TIMER_EXAMPLE_PERIOD(31250Hz) resolution
	*/
	tc_set_resolution(&TIMER_EXAMPLE, TIMER_EXAMPLE_PERIOD);

	do {
		/* Go to sleep, everything is handled by interrupts. */
		sleepmgr_enter_sleep();
	} while (1);
}