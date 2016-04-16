/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#ifndef ISRS_H
#define ISRS_H

#include "music.h"
#include "isr.h"
#include "globals.h"

#define VBL_ISR  28
#define IKBD_ISR 70

typedef void (*Vector)();


extern Vector VBL_orig_vector;
extern Vector IKBD_orig_vector;

extern UINT8 head;
extern UINT8 tail;

extern UINT8 IKBD_buffer[256];

extern int music_ticks;
extern int score_ticks;
extern int enemy_ticks;
extern int render_request; 


void do_VBL_ISR();
void do_IKBD_ISR();

void install_vectors();
void remove_vectors();

Vector install_vector(int num, Vector vector);

void mask_interrupts();
void unmask_interrupts();

#endif