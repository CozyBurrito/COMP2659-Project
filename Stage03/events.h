#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'


void move_player_ship(struct Model *modelPtr, UINT16 player);
void move_enemy_ship(struct Model *modelPtr, UINT16 enemy);
void player_collision(struct Model *modelPtr, UINT16 player);
UINT8 game_over(struct Model *modelPtr);


#endif