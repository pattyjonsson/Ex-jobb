/*
 * ISR_Handler.c
 *
 * Created: 2016-01-13 09:06:14
 *  Author: Patricia Jönsson and Martin Bråhagen
 */ 

#include <asf.h>
#include "asf.h"
#include "ISR_Handler.h"
#include "initDA.h"
#include <inttypes.h>

// Array filled with bits representing a voltage value 
uint32_t outputDA[] = {1753,1983,2214,2444,2675,2444,2214,1983,1753,1522,1291,1061,830,1061,1291,1522};
int32_t slumptal;
uint32_t value;
uint32_t count; //Global counter

void TC5_Handler() /* function name defined by ASF */
{
	pmc_enable_periph_clk(ID_TRNG);
	trng_enable(TRNG); 
	volatile uint32_t ul_dummy; 
	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC1, 2);
	tc_get_
	UNUSED(ul_dummy); /* Avoid compiler warning */
	slumptal = trng_read_output_data(TRNG);
	slumptal=slumptal%(2*184)-184;	// Either adds +0.1 V or -0.1V 
	value = outputDA[count]+slumptal;
	count++;
	if(count>15) // 16 steps the start over
	{
		count = 0;
	}
	dacc_write_conversion_data(DACC,value);
}