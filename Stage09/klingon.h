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

void play_klingon();
typedef void (*Vector)();
Vector install_vector(int num, Vector vector);

#endif