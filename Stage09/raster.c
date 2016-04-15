/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include <stdlib.h>

#include "raster.h"

/*Original plot_pixel function, given the location of the screen in memory 
and a position on that screen, will draw a bitmap image pixel by pixel to the screen*/
void plot_pixel(UINT8 *base, int x, int y) {
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		*(base + y * 80 + (x >> 3)) |= 1 << (7 - (x & 7));
	}

}

/*Prints a line given a start and end point on the screen
The function will print diagonal lines by averaging small segments
of the line in order to make up for pixels that don't line up nicely*/
void print_line(UINT8 *base, int x0, int y0, int x1, int y1) {
	int dx = abs(x1-x0);
	int sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0);
	int sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2;
	int e2;
	
	while(x0 != x1 || y0 != y1){ 
		plot_pixel(base,x0,y0);
		e2 = err;
		
		if(e2 >-dx) {
			err -= dy; 
			x0 += sx;
		}
		
		if(e2 < dy) {
			err += dx; 
			y0 += sy;
		}
	
	}
	
}

/*writes a character to the screen in the FAT font as chosen for the game*/
void print_char(UINT8 *base, int x, int y, char ch) {
	int i = 0;
	UINT8 *char_hex = GLYPH_START_FAT(ch);
	
	for(i = 0; i < 16; i++, char_hex++) {
		*(base + (y + i) * 80 + (x >> 3)) = *char_hex;
	}
	
}

/*prints an array of chars to the screen*/
void print_string(UINT8 *base, int x, int y, char str[]) {
	int i = 0;
	
	while(str[i] != '\0') {
		print_char(base, x, y, str[i]);
		x += 8;
		i++;
	}
	
}

void print_clr_num(UINT8 *base, int x, int y) {
	int i = 0;
	
	for(i = 0; i < 16; i++) {
		*(base + (y + i) * 20 + (x >> 5)) &= 0x00000000;
	}
	
}

/*prints digits to the screen*/
void print_num(UINT8 *base, int x, int y, UINT16 num) {
	char a, b, c, d;
	
	a = (num % 10) + '0';
	num /= 10;
	
	b = (num % 10) + '0';
	num /= 10;
	
	c = (num % 10) + '0';
	num /= 10;
	
	d = (num % 10) + '0';
	
	print_char(base, x, y, d);
	print_char(base, x+8, y, c);
	print_char(base, x+16, y, b);
	print_char(base, x+24, y, a);
	
}

/*calls marks clr_qk*/
void clear_screen(long *base) {
	clr_scrn(base);
}

/*plots a bitmap 64 bits long by a specified height*/
void plot_bitmap_64_byte(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
	int i = 0,
		j = 0,
	 	k = 0;
	
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		for (i = 0; i < height; i++) {
			for(k = 0; k < 8; k++) {
				*(base + (y + i) * 80 + ((x >> 3) + k)) |= bitmap[j++];
			}
		}
		
	}

}

/*Don's plot bitmap, won't work with the bitmaps we shuffled up (ships)*/
void plot_screen(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 80; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(80*i)+(80-k)];
         }
      }
   }
   
/*Don's plot bitmap used to make the title screen selector move*/
/*This should be made into a neater function that can be passed a bitmap and values*/
void plot_bitmap_32(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 4; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(4*i)+(3-k)];
         }
      }
   }

/*these plot functions could be combined, no time. They work.*/
void clear_area(UINT8 *base, int x, int y){
	int i = 0,
    k = 0;

    for (i = 0; i < 32; i++){
        for (k =0; k < 4; k++){
           *(base + ((y+i) * 80) + ((x >> 3) + k)) &= rocket_empty[(4*i)+(3-k)];
        }
    }
}
