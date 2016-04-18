/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#ifndef BITMAPS_H
#define BITMAPS_H

#include "globals.h"

extern const UINT8 empty[];
extern const UINT8 en_ship[];
extern const UINT8 p1_ship[];
extern const UINT8 fat[];
extern const UINT8 splash[];
extern const UINT8 rocket_left[];
extern const UINT8 rocket_right[];
extern const UINT8 rocket_empty[];

extern const UINT16 mouse_cursor[];
extern UINT32 mouse_bkgd[];

#define CHAR_BEL    7
#define CHAR_TAB    9
#define CHAR_LF    10
#define CHAR_VT    11
#define CHAR_FF    12
#define CHAR_CR    13
#define CHAR_DEL  127

#define IS_PRINTABLE(i) ((i) >= ' ' && (i) <= '~')
#define GLYPH_START_FAT(i) (fat + (((i) - ' ') << 4))

#endif
