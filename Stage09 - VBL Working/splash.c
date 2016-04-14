/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <linea.h>

#include "klingon.h"

UINT8 buffer[35256];

/*Don's plot pixel*/
void plot_bitmap_64_byte(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 4; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(4*i)+(3-k)];
         }
      }
   }
   
void splash_screen(){
	    UINT8 *base = (UINT8 *)get_video_base();
		
		orig_vector = install_vector(VBL, vbl_isr);
		
		plot_bitmap_64_byte(base, 0, 0, splash, 400);
}


