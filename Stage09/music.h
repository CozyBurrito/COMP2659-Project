/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.h"
#include "globals.h"

void start_sound();
UINT8 update_music(UINT32 time_elapsed); 

#endif