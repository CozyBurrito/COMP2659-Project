/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#ifndef SYS_H
#define	SYS_H

#include "globals.h"

void kbd_isr();
UINT16* get_video_base();
void set_video_base(UINT16 *base);

void vbl_isr();

#endif