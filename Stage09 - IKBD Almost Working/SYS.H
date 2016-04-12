#ifndef SYS_H
#define	SYS_H

#include "globals.h"

UINT16* get_video_base();
void set_video_base(UINT16 *base);

void vbl_isr();
void ikbd_isr();

#endif