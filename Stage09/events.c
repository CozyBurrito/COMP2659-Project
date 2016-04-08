#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "events.h"
#include "model.h"
#include "effects.h"

UINT8 move_player_ship(struct Model *modelPtr, UINT16 player) {
	UINT8 has_moved = 0;
	UINT8 direction;
	
	UINT16 player_posX;
	UINT16 player_posY;
	
	UINT16 player_deltaX;
	UINT16 player_deltaY;
	
	
	if (get_player_move_requested(modelPtr, player)) {
		direction = get_player_move_requested_direction(modelPtr, 0);
		
		player_posX = get_player_posX(modelPtr, player);
		player_posY = get_player_posY(modelPtr, player);
		
		player_deltaX = get_player_deltaX(modelPtr, player);
		player_deltaY = get_player_deltaY(modelPtr, player);
		
		if(direction == UP && player_posY > 0) {
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

		
		if (has_moved) {
			set_player_cor(modelPtr, player, player_posX, player_posY);
		}
		
		set_player_move_requested(modelPtr, 0, 0);
		
	}
	
	return has_moved;
}

void request_player_move(struct Model *modelPtr, UINT16 player, UINT8 direction) {
	UINT8 is_valid_char = 0;
	
	if(	direction == UP 	||
		direction == DOWN 	||
		direction == LEFT 	||
		direction == RIGHT		) 
		{
			is_valid_char = 1;
		}
	if(is_valid_char && !get_player_alive(modelPtr, player)) {
		set_player_move_requested(modelPtr, player, 1);
		set_player_move_requested_direction(modelPtr, player, direction);
	}
	
}

void move_enemy_ship(struct Model *modelPtr, UINT16 enemy) {	
	UINT16 enemy_posX;
	UINT16 enemy_deltaX;
	
	enemy_posX = get_enemy_posX(modelPtr, enemy);
	enemy_deltaX = get_enemy_deltaX(modelPtr, enemy);
	
	if (enemy_posX <= 568) {
		enemy_posX -= enemy_deltaX;
		set_enemy_cor(modelPtr, enemy, enemy_posX, get_enemy_posY(modelPtr,enemy));
	}
	else {
		generate_enemy(modelPtr, enemy);
	}
	
}

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


UINT8 game_over(struct Model *modelPtr) {
	return get_player_alive(modelPtr, 0);
}


long kbd_is_waiting() {
	return Cconis();
}

long kbd_read_char() {
	return Cnecin();
}
