/*
 * delay.c
 *
 * Created: 2017-04-03 12:11:25
 *  Author: Patricia
 */ 

void delay(uint16_t length){
	for(uint16_t i=0; i<length; i++){
		for(uint8_t j=0; j<255; j++){
			asm volatile ("nop");
		}
	}
}