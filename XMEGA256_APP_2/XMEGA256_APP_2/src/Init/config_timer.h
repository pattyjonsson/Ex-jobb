/*
 * config_timer.h
 *
 * Created: 2017-06-13 14:42:47
 *  Author: Patricia
 */ 

#include "asf.h"

#ifndef CONFIG_TIMER_H_
#define CONFIG_TIMER_H_

#define TIMER_EXAMPLE        TCC0

/*
*This example runs at default 2MHz system clock
*/
#define	TIMER_EXAMPLE_PERIOD 312
#define TIMER_PORT_LED       TCE0

void config_timer(void);

#endif /* CONFIG_TIMER_H_ */