/*
 * timer.c
 *
 * Created: 2016-01-13 08:34:50
 *  Author: Patricia
 */ 


#include "timer.h"
#include "asf.h"


static void configure_tc()
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t freq;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	freq = ((930425 % 1979) + 1013);
	freq = (freq*16);
	
	/* Configure power management of timer clocks */
	pmc_enable_periph_clk(ID_TC3);
	/* Configure TC for a 20,928 kHz frequency and trigger on
	RC compare. */
	tc_find_mck_divisor(freq, ul_sysclk, &ul_div,
	&ul_tcclks, ul_sysclk);
	tc_init(TC1, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC1, 0, (ul_sysclk / ul_div) / freq);
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC3);
	tc_enable_interrupt(TC1, 0, TC_IER_CPCS);
	tc_start(TC1, 0);
}