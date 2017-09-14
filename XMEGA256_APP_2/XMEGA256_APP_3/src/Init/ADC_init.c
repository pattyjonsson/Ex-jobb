/*
 * ADC_init.c
 *
 * Created: 2017-06-13 14:42:08
 *  Author: Patricia
 */ 
 #include "asf.h"
 #include "ADC_init.h"

 /************************************************************************/
 /* Initialize  ADC                                                                     */
 /************************************************************************/

 void ADC_init(void){
	 CCP=0xD8;
	 CLK.PSCTRL=CLK_PSADIV_1_gc;
	 ADCA.CTRLB=ADC_CURRLIMIT_HIGH_gc;
	 ADCA.REFCTRL=ADC_REFSEL_INTVCC_gc;
	 ADCA.PRESCALER=ADC_PRESCALER_DIV4_gc;
	 ADCA.CH0.CTRL= ADC_CH_INPUTMODE_SINGLEENDED_gc;
	 ADCA.CH0.MUXCTRL=ADC_CH_MUXPOS_PIN0_gc;
	 ADCA.CH0.INTCTRL=ADC_CH_INTMODE_COMPLETE_gc | ADC_CH_INTLVL_HI_gc;
	 ADCA.CTRLA=ADC_ENABLE_bm;
 }