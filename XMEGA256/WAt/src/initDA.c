/*
 * initDA.c
 *
 * Created: 2016-01-12 13:04:41
 *  Author: Patricia Jönsson and Martin Bråhagen
 */ 


#include "initDA.h"
#include "asf.h"
#include <inttypes.h>


int daccInit()
{
	int result = 1;
	pmc_enable_periph_clk(ID_DACC); /* DACC clock should be enabled before using it. */
	dacc_reset(DACC); /* Reset DACC */
	dacc_set_transfer_mode(DACC, 0); /* Configure FIFO transfer mode */
	dacc_set_timing(DACC,1,1,0); /* 1 is shortest refresh period, 1 max. speed, 0 startup time */
	dacc_set_channel_selection(DACC,0); /* Disable flexible (TAG) mode and select channel 0 for DAC output */
	result = _enable_channel(DACC, 0); /* Enable DAC channel 0 */
	return result;
}

