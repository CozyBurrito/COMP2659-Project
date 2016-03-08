#ifndef RASTER_H
#define RASTER_H

#include "fat.h"
#include "clr_qk.h"
#include "globals.h"

void plot_pixel(UINT8 *base, int x, int y);
void print_line(UINT8 *base, int x0, int y0, int x1, int y1);
void print_char(UINT8 *base, int x, int y, char ch);
void print_string(UINT8 *base, int x, int y, char *str);
void print_num(UINT8 *base, int x, int y, UINT16 num);
void print_clr_num(UINT8 *base, int x, int y);
void clear_screen();
void plot_bitmap_64_byte(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height);

#endif