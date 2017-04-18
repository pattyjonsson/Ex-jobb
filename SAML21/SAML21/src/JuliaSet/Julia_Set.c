/*
 * Julia_Set.c
 *
 * Created: 2017-04-17 11:51:46
 *  Author: Patricia
 */ 

 #include "Julia_Set.h"
 #include "asf.h"
 #include "complex.h"

/* void GenerateJulia_fpu(uint16_t size_x, uint16_t size_y, uint16_t
 offset_x, uint16_t offset_y, uint16_t zoom, uint8_t *buffer){

 float tmp1, tmp2;
 float num_real, num_img;
 float radius;
 uint8_t i;
 uint16_t x,y;

 for (y=0; y<size_y; y++)
 {
	 for (x=0; x<size_x; x++)
	 {
		 num_real = y - offset_y;
		 num_real = num_real / zoom;
		 num_img = x - offset_x;
		 num_img = num_img / zoom;
		 i=0;
		 radius = 0;
		 
		 while ((i<50-1) && (radius < 4))
		 {
			 tmp1 = num_real * num_real;
			 tmp2 = num_img * num_img;
			 num_img = 2*num_real*num_img + (4+3*I);
			 num_real = tmp1 - tmp2 + 7;
			 radius = tmp1 + tmp2;
			 i++;
		 }
		 /* Store the value in the buffer */
		/* buffer[x+y*size_x] = i;
	 }
 }
 }
 */