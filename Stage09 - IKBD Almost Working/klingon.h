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

long kbd_is_waiting();
char kbd_read_char();

#endif