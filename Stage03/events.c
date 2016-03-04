#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "events.h"


void move_player_ship(struct Model *modelPtr, UINT16 player) {
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
		else if(direction == DOWN && player_posY < SCREEN_HEIGHT) {
			player_posY += player_deltaY;
			has_moved = 1;
		}
		else if(direction == LEFT && player_posX > 0) {
			player_posX -= player_deltaX;
			has_moved = 1;
		}
		else if(direction == RIGHT && player_posX < SCREEN_WIDTH) {
			player_posX += player_deltaX;
			has_moved = 1;
		}

		if (has_moved) {
			set_player_cor(modelPtr, player, player_posX, player_posY);
		}
		
		set_player_move_requested(modelPtr, 0, 0);
		
	}
	
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
	UINT16 enemy_posX = get_enemy_posX(modelPtr, enemy);
	
	if (enemy_posX > 0) {
		enemy_posX -= 8;
		set_enemy_cor(modelPtr, enemy, enemy_posX, 200);
	}
	else {
		set_enemy_cor(modelPtr, enemy, 500, 200);
	}

}

void player_collision(struct Model *modelPtr, UINT16 player) {
	set_player_alive(modelPtr, player, 1);
}


/*
void enemy_collision(struct Model *modelPtr, UINT16 enemy) {
}
*/

/*
void update_score(struct Model *modelPtr) {
)
*/


UINT8 game_over(struct Model *modelPtr) {
	return get_player_alive(modelPtr, 0);
}


