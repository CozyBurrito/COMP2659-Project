/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "raster.h"
#include "model.h"
#include "globals.h"


void render_model(struct Model *modelPtr, UINT8 *base, UINT8 has_moved);
void render_ship(struct Model *modelPtr, UINT8 *base, UINT8 ship, UINT16 ship_num);
void render_score(struct Model *modelPtr, UINT8 *base);
void render_line(UINT8 *base);

void render_splash_screen(UINT8 *base);
void render_rocket(UINT8 *base, UINT8 location);

#endif