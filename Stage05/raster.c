#include <osbind.h>
#include <stdlib.h>

#include "raster.h"

void plot_pixel(UINT8 *base, int x, int y) {
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		*(base + y * 80 + (x >> 3)) |= 1 << (7 - (x & 7));
	}

}

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

void print_char(UINT8 *base, int x, int y, char ch) {
	int i = 0;
	UINT8 *char_hex = GLYPH_START_FAT(ch);
	
	for(i = 0; i < 16; i++, char_hex++) {
		*(base + (y + i) * 80 + (x >> 3)) = *char_hex;
	}
	
}

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

void clear_screen(long *base) {
	clr_scrn(base);
}


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