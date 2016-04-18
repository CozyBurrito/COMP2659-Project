/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>

#include "events.h"

char *ascii_tbl = 0xFFFE829C;

/* 
Purpose: Moves a players ship in the requested direction if there is a request to move the ship
Param: pointer to model
       player num: 0 = player 1, 1 = player 2
*/
UINT8 move_player_ship(struct Model *modelPtr, UINT16 player) {
	UINT8 has_moved = 0;
	UINT8 direction;
	
	UINT16 player_posX;
	UINT16 player_posY;
	
	UINT16 player_deltaX;
	UINT16 player_deltaY;
	
	/* Check of the move was requested */
	if (get_player_move_requested(modelPtr, player)) {
        
        /* Get the direction the player requested to move in */
		direction = get_player_move_requested_direction(modelPtr, 0);
		
        /* Get player x and y */
		player_posX = get_player_posX(modelPtr, player);
		player_posY = get_player_posY(modelPtr, player);
		
        /* Get player "speed" values */
		player_deltaX = get_player_deltaX(modelPtr, player);
		player_deltaY = get_player_deltaY(modelPtr, player);
		
        /* Process the move */
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

		/* set the new player's coordinates */
		if (has_moved) {
			set_player_cor(modelPtr, player, player_posX, player_posY);
		}
		
        /* Turn the move request flag off */
		set_player_move_requested(modelPtr, 0, 0);
		
	}
	
	return has_moved;
}

/* 
Purpose: Set the request to true (in the model) if a valid direction is given
Param: pointer to model
       player num: 0 = player 1, 1 = player 2
       direction: the "key" that was requested to be processed
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
    
    /* If the move was in a valid direction and the player is alive, then set the request to "true" and save the direction */   
	if(is_valid_char && !get_player_alive(modelPtr, player)) {
		set_player_move_requested(modelPtr, player, 1);
		set_player_move_requested_direction(modelPtr, player, direction);
	}
	
}

/*
Purpose: Moves the enemy ship to a new coordinate, and resets it if needed
Param: pointer to model
       enemy num: 0 = enemy 1, 1 = enemy 2, ...
*/
void move_enemy_ship(struct Model *modelPtr, UINT16 enemy) {	
	UINT16 enemy_posX;
	UINT16 enemy_deltaX;
	
    /* Get enemy's current position, and "speed" */
	enemy_posX = get_enemy_posX(modelPtr, enemy);
	enemy_deltaX = get_enemy_deltaX(modelPtr, enemy);
	
    /* Update the enemies position if it isn't on the left side of the screen */
	if (enemy_posX <= 568) {
		enemy_posX -= enemy_deltaX;
		set_enemy_cor(modelPtr, enemy, enemy_posX, get_enemy_posY(modelPtr,enemy));
	}
	else {
        /* If it is on the left side of the screen, then generate a new starting position */
		generate_enemy(modelPtr, enemy);
	}
	
}
/*
Purpose: checks to see if any part of the player ship is occupying any of the
         same space as an enemy
Param: pointer to model
       enemy num: 0 = enemy 1, 1 = enemy 2, ...
       player num: 0 = player 1, 1 = player 2
*/
void collision(struct Model *modelPtr, UINT16 enemy, UINT16 player){
	/* Get player positions */
    UINT16 playerX = get_player_posX(modelPtr,player);
	UINT16 playerY = get_player_posY(modelPtr, player);
    
    /* Get enemy positions */
	UINT16 enemyX = get_enemy_posX(modelPtr, enemy);
	UINT16 enemyY = get_enemy_posY(modelPtr, enemy);
	
    /* Check if that player is in the same space as the enemy */
	if((playerX+64 >= enemyX && playerX <= enemyX+64) &&
	    (playerY+32 >= enemyY && playerY <= enemyY+32))
		{
            /* Set that player to "dead" */
			set_player_alive(modelPtr, player, 1);
		}
		
}

/*
Purpose: Checks to see if player is still alive (hasn't collided with enemy)
Param: pointer to model
Return: 0 = player alive, 1 = player dead
*/
UINT8 game_over(struct Model *modelPtr) {
	return get_player_alive(modelPtr, 0);
}


/* 
Purpose: Reads a value from buffer
Return: Long with scancode and ascii value
        Hi Word = Scancode
        Low Word = Ascii value
*/
long kbd_read_char() {
	/* long ret;
    
	mask_interrupts();
	
     read the scancode from buffer, and then put ascii value 
	ret = IKBD_buffer[head];
	ret = ret << 16;
	ret = ret + *(ascii_tbl + IKBD_buffer[head++]);
	
	unmask_interrupts();
    
	return ret; */
    
    return Cnecin();
}


/* 
Purpose: Checks to see if buffer is empty
Return: true = not empty
        false = empty
*/
long kbd_is_waiting() {
	/* return head != tail; */
    return Cconis();
}


/* 
Purpose: Empty the buffer
*/
void clear_kbd_buffer() {
    /* Keep going until buffer is empty */
	while(kbd_is_waiting()) {
		head++;
	}
    
    /* Clear the last value */
	IKBD_buffer[tail] = 0x00;
}

