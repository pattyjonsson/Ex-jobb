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
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
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

#define M 3

void rtc_overflow_callback(void);
void configure_rtc_count(void);
void configure_rtc_callbacks(void);
void configure_adc(void);


struct rtc_module rtc_instance;
struct adc_module adc_instance;

void rtc_overflow_callback(void)
{
	uint16_t result;
	adc_start_conversion(&adc_instance);
	adc_read(&adc_instance, &result);

	static float xbuff[M+1]={0};
	static float b[M+1]={0.2500,0.2500,0.2500,0.2500};

	float sum;

	for (int k=M; k>0; k--){
		xbuff[k]=xbuff[k-1];
	}
	xbuff[0]=(float)result;

	for (int i=0; i<=M; i++){
	sum +=(xbuff[i]*b[i]);
	}

	//Add "sending" value
}



void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}




void configure_rtc_count(void)
{

	struct rtc_count_config config_rtc_count;
	rtc_count_get_config_defaults(&config_rtc_count);

	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;
	#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config_rtc_count.continuously_update = true;
	#endif

	rtc_count_init(&rtc_instance, RTC, &config_rtc_count);

	rtc_count_enable(&rtc_instance);

}


void configure_rtc_callbacks(void)
{

	rtc_count_register_callback(
	&rtc_instance, rtc_overflow_callback, RTC_COUNT_CALLBACK_OVERFLOW);

	rtc_count_enable_callback(&rtc_instance, RTC_COUNT_CALLBACK_OVERFLOW);

}


int main(void)
{

	system_init();

	configure_rtc_count();
	configure_adc();

	configure_rtc_callbacks();

	rtc_count_set_period(&rtc_instance, 2000);


	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	while (true) {
		system_sleep();
		
	}

}
