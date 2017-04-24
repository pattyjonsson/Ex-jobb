/**
 * \file
 *
 * \brief FreeRTOS demo application main function.
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
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

#include <asf.h>
#include "demotasks.h"
#include <conf_demo.h>

#define LED_TASK_PRIORITY     (tskIDLE_PRIORITY + 2)
#define SLEEP_TASK_PRIORITY		(tskIDLE_PRIORITY + 1)

static void led_toggle(void){

port_pin_set_output_level(LED_0_PIN,LED_0_ACTIVE);
port_pin_set_output_level(LED_0_PIN,!LED_0_ACTIVE);

}

static void sleep(void){
//system_sleep();




}

int main (void)
{
	system_init();
	system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE);

	// Initialize the demo..
	//demotasks_init();
	xTaskCreate(sleep,(const char *)"sleep",	configMINIMAL_STACK_SIZE,	NULL,	SLEEP_TASK_PRIORITY,	NULL);

	xTaskCreate(led_toggle,(const char *)"toggle led",	configMINIMAL_STACK_SIZE,	NULL,	LED_TASK_PRIORITY,	NULL);

	// ..and let FreeRTOS run tasks!
	vTaskStartScheduler();

	do {
		// Intentionally left empty
	} while (true);
}
