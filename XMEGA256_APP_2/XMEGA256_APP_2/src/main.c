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
#include "Init/config_timer.h"


/************************************************************************/
/* Disable JTAG to lower power consumption                              */
/************************************************************************/
static void disable_JTAG(void){
	CCP = CCP_IOREG_gc;
	MCU.MCUCR=MCU_JTAGD_bm;
}

/************************************************************************/
/* Disable unused peripherals to save power                             */
/************************************************************************/
static void disable_peripherals(void){
	PR.PRGEN=PR_USB_bm | PR_AES_bm  | PR_EVSYS_bm | PR_DMA_bm | PR_RTC_bm ;

	PR.PRPA=PR_DAC_bm | PR_AC_bm;
	PR.PRPB=PR_DAC_bm | PR_AC_bm | PR_ADC_bm;

	PR.PRPC= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm |  PR_TC1_bm;
	PR.PRPD= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC0_bm | PR_TC1_bm;
	PR.PRPE= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm |  PR_TC1_bm;
	PR.PRPF= PR_TWI_bm | PR_USART0_bm | PR_USART1_bm | PR_SPI_bm | PR_HIRES_bm | PR_TC0_bm | PR_TC1_bm;
}

int main (void)
{
	/*Setup system*/
	pmic_init();
	board_init();
	sysclk_init();
	/*Disable JTAG and other peripherals not used to save power*/
	disable_JTAG();
	disable_peripherals();
	/*Initialize ADC*/
	adc_enable(&ADCA);
	/*Initialize interrupts */		
	cpu_irq_enable();
	/*Initialize TC-timer*/
	config_timer();
	/*Set pin as output*/
	ioport_set_pin_dir(J1_PIN1, IOPORT_DIR_OUTPUT);
	/*Setting the sleep mode*/
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();

	while(1){
	sleep_cpu();
	
	}
}
