/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "events.h"
#include "model.h"
#include "effects.h"

/* 
moves a players ship in the requested direction if there is a request to move the ship
*/
UINT8 move_player_ship(struct Model *modelPtr, UINT16 player) {
	UINT8 has_moved = 0;
	UINT8 direction;
	
	UINT16 player_posX;
	UINT16 player_posY;
	
	UINT16 player_deltaX;
	UINT16 player_deltaY;
	
	
	if (get_player_move_requested(modelPtr, player)) {  /* Check if a move was requested */
		direction = get_player_move_requested_direction(modelPtr, 0);
		
		player_posX = get_player_posX(modelPtr, player);
		player_posY = get_player_posY(modelPtr, player);
		
		player_deltaX = get_player_deltaX(modelPtr, player);
		player_deltaY = get_player_deltaY(modelPtr, player);
		
		if(direction == UP && player_posY > 0) {    /* move the players ship*/
			player_posY -= player_deltaY;
			has_moved = 1;
		}
		else if(direction == DOWN && player_posY < SCREEN_HEIGHT - 88) {
			player_posY += player_deltaY;
			has_moved = 1;
		}
		else if(direction == LEFT && player_posX > player_deltaX) {
			player_posX -= player_deltaX;
			has_moved = 1;
		}
		else if(direction == RIGHT && player_posX < SCREEN_WIDTH - 64) {
			player_posX += player_deltaX;
			has_moved = 1;
		}

		
		if (has_moved) {    /* if it actaully moved in a valid direction, then give the player the new coordinates */
			set_player_cor(modelPtr, player, player_posX, player_posY);
		}
		
		set_player_move_requested(modelPtr, 0, 0);
		
	}
	
	return has_moved;
}

/* 
set the request to true if a valid direction is given
*/
void request_player_move(struct Model *modelPtr, UINT16 player, UINT8 direction) {
	UINT8 is_valid_char = 0;
	
	if(	direction == UP 	||
		direction == DOWN 	||
		direction == LEFT 	||
		direction == RIGHT		) 
		{
			is_valid_char = 1;
		}
	if(is_valid_char && !get_player_alive(modelPtr, player)) { /* if it's a valid char and the player is alive request the move */
		set_player_move_requested(modelPtr, player, 1);
		set_player_move_requested_direction(modelPtr, player, direction);
	}
	
}

/* 
given an enemy,
move it's ship
*/
void move_enemy_ship(struct Model *modelPtr, UINT16 enemy) {	
	UINT16 enemy_posX;
	UINT16 enemy_deltaX;
	
	enemy_posX = get_enemy_posX(modelPtr, enemy);
	enemy_deltaX = get_enemy_deltaX(modelPtr, enemy);
	
	if (enemy_posX <= 568) {    /* if it's not on the edge of the screen then move it */
		enemy_posX -= enemy_deltaX;
		set_enemy_cor(modelPtr, enemy, enemy_posX, get_enemy_posY(modelPtr,enemy));
	}
	else { /* otherwise generate a new starting position */
		generate_enemy(modelPtr, enemy);
	}
	
}

/* 
check if the player collieded with a given enemy
*/
void collision(struct Model *modelPtr, UINT16 enemy, UINT16 player){
	int playerX = get_player_posX(modelPtr,player);
	int playerY = get_player_posY(modelPtr, player);
	int enemyX = get_enemy_posX(modelPtr, enemy);
	int enemyY = get_enemy_posY(modelPtr, enemy);
	
	if((playerX+64 >= enemyX && playerX <= enemyX+64) &&
	    (playerY+32 >= enemyY && playerY <= enemyY+32))
		{
			set_player_alive(modelPtr, player, 1);
		}
		
}

/*
int enemy_collision(struct Model *modelPtr, int thisEnemyY, UINT16 enemy){
	int collision = 0;
	int i = 0;
	
	UINT16 thisEnemyX = get_enemy_posX(modelPtr, enemy);
	
	UINT16 otherEnemyX;
	UINT16 otherEnemyY;
	
	for(i = 0; i < NUM_ENEMIES && get_active(modelPtr,i) && !collision; i++) {
		otherEnemyX = get_enemy_posX(modelPtr, i);
		otherEnemyY = get_enemy_posY(modelPtr, i);
	
		if(thisEnemyX <= otherEnemyX+80 && thisEnemyX >= otherEnemyX) {
			collision = 1;
		}
	}

	return collision;
}*/

/* check if the game is over */
UINT8 game_over(struct Model *modelPtr) {
	return get_player_alive(modelPtr, 0);
}

