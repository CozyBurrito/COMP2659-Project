#ifndef RENDERER_H
#define RENDERER_H

#include "raster.h"
#include "model.h"
#include "p1_ship.h"
#include "en_ship.h"
#include "empty.h"
#include "globals.h"


void init_render(UINT8 *base);
void render_model(struct Model *modelPtr, UINT8 *base);
void render_ship(struct Model *modelPtr, UINT8 *base, UINT8 ship, UINT16 ship_num);
void render_score(struct Model *modelPtr, UINT8 *base);
void render_line(UINT8 *base);

#endif