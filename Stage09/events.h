/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"


UINT8 move_player_ship(struct Model *modelPtr, UINT16 player);

void move_enemy_ship(struct Model *modelPtr, UINT16 enemy);

void request_player_move(struct Model *modelPtr, UINT16 player, UINT8 direction);

void collision(struct Model *modelPtr, UINT16 enemy, UINT16 player);

UINT8 game_over(struct Model *modelPtr);

int enemy_collision(struct Model *modelPtr, int enemyY, UINT16 enemy);

#endif