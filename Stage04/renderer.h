#ifndef RENDERER_H
#define RENDERER_H

#include "raster.h"
#include "model.h"
#include "p1_ship.h"
#include "empty.h"
#include "globals.h"


void render_model(struct Model *modelPtr, UINT8 *base);
void render_player(struct Model *modelPtr, UINT8 *base, UINT16 player);
void render_score(struct Model *modelPtr, UINT8 *base);
void render_line(UINT8 *base);

#endif