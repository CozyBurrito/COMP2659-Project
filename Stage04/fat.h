#ifndef FAT_H
#define FAT_H

#include "globals.h"

extern const UINT8 fat[];

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
