/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#ifndef KLINGON_H
#define KLINGON_H

#include "model.h"
#include "events.h"
#include "renderer.h"
#include "globals.h"
#include "music.h"
#include "effects.h"
#include "sys.h"

#define VBL 28
#define IKBD 70

typedef void (*Vector)();
Vector install_vector(int num, Vector vector);

void do_VBL_ISR();
void do_IKBD_ISR();

void play_klingon();
void install_vectors();
void remove_vectors();

UINT8 kbd_is_waiting();
UINT8 kbd_read_char();

#endif