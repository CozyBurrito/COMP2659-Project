/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>

#include "events.h"

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
	
	
	if (get_player_move_requested(modelPtr, player)) {
		direction = get_player_move_requested_direction(modelPtr, 0);
		
		player_posX = get_player_posX(modelPtr, player);
		player_posY = get_player_posY(modelPtr, player);
		
		player_deltaX = get_player_deltaX(modelPtr, player);
		player_deltaY = get_player_deltaY(modelPtr, player);
		
		if(direction == KBD_W && player_posY > 0) {
			player_posY -= player_deltaY;
			has_moved = 1;
		}
		else if(direction == KBD_S && player_posY < SCREEN_HEIGHT - 88) {
			player_posY += player_deltaY;
			has_moved = 1;
		}
		else if(direction == KBD_A && player_posX > player_deltaX) {
			player_posX -= player_deltaX;
			has_moved = 1;
		}
		else if(direction == KBD_D && player_posX < SCREEN_WIDTH - 64) {
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

/* 
set the request to true if a valid direction is given
*/
void request_player_move(struct Model *modelPtr, UINT16 player, UINT8 direction) {
	UINT8 is_valid_char = 0;
	
	if(	direction == KBD_W 	||
		direction == KBD_S 	||
		direction == KBD_A 	||
		direction == KBD_D	) 
		{
			is_valid_char = 1;
		}
        
	if(is_valid_char && !get_player_alive(modelPtr, player)) {
		set_player_move_requested(modelPtr, player, 1);
		set_player_move_requested_direction(modelPtr, player, direction);
	}
	
}

/*
moves the enemy ship to a new coordinate
*/
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
/*
checks to see if any part of the player ship is occupying any of the
same space as an enemy
*/
void collision(struct Model *modelPtr, UINT16 enemy, UINT16 player){
	UINT16 playerX = get_player_posX(modelPtr,player);
	UINT16 playerY = get_player_posY(modelPtr, player);
	UINT16 enemyX = get_enemy_posX(modelPtr, enemy);
	UINT16 enemyY = get_enemy_posY(modelPtr, enemy);
	
	if((playerX+64 >= enemyX && playerX <= enemyX+64) &&
	    (playerY+32 >= enemyY && playerY <= enemyY+32))
		{
			set_player_alive(modelPtr, player, 1);
		}
		
}

/*
returns a value if the player hasn't collided with an enemy
*/
UINT8 game_over(struct Model *modelPtr) {
	return get_player_alive(modelPtr, 0);
}


UINT8 kbd_read_char() {
	UINT8 key;
    
	mask_interrupts();
	
	key = IKBD_buffer[head++];
	
	unmask_interrupts();
    
	return key;
}

bool kbd_is_waiting() {
	return head != tail;
}

