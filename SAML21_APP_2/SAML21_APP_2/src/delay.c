/*
 * delay.c
 *
 * Created: 2017-04-27 11:52:41
 *  Author: Patricia
 */ 

 #include "delay.h"
 #include "asf.h"



 void delay (uint16_t length)
 {
	 // Simple delay loop
	 for (uint16_t i=0; i<length; i++) {
		 for (uint8_t j=0; j<255; j++) {
			 asm volatile("nop");
		 }
	 }
	 }