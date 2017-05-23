/*
 * timer.c
 *
 * Created: 2016-01-13 08:34:50
 *  Author: Patricia Jönsson and Martin Bråhagen
 */ 


#include "interupttimer.h"
#include "asf.h"

uint32_t frekvens = (((910604 % 1979) + 1013)*16); // frequency calculation based on day of birth

static void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	/* Configure power management of timer clocks */
	pmc_enable_periph_clk(ID_TC5);
	/* Configure TC for a 20,928 kHz frequency and trigger on
	RC compare. */
	tc_find_mck_divisor(frekvens, ul_sysclk, &ul_div,
	&ul_tcclks, ul_sysclk);
	tc_init(TC1, 2, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC1, 2, (ul_sysclk / ul_div) / frekvens);
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC5);
	tc_enable_interrupt(TC1, 2, TC_IER_CPCS);
	tc_start(TC1, 2);
}

void inializeconfig_tc(void)
{
	configure_tc();
}