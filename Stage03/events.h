#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"


void move_player_ship(struct Model *modelPtr, UINT16 player);
void move_enemy_ship(struct Model *modelPtr, UINT16 enemy);

void request_player_move(struct Model *modelPtr, UINT16 player, UINT8 direction);

void collision(struct Model *modelPtr, UINT16 enemy, UINT16 player);
void update_score(struct Model *modelPtr);
UINT8 game_over(struct Model *modelPtr);


#endif