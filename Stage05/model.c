#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "model.h"
#include "events.h"
#include "renderer.h"
#include "globals.h"
/** init_model: Used to initialize the values of a given model.  
 * 				It takes a pointer to a model and changes it's values 
 * 				to set values, instead of having to call all of the
 * 	 			functions individually.
 * 
 * @param: modelPtr 
 * 		   A pointer to an object of the Model structure type.
 * 
 * @return: none
 * 
 */
void init_model(struct Model *modelPtr) {	
	int i;
	int enemyY;
	
	set_score(modelPtr, 0); 	/* initialize score to 0 */
	set_player_move_requested(modelPtr, 0, 0);
	
	set_player_deltaX(modelPtr, 0, 8);
	set_player_deltaY(modelPtr, 0, 8);
	
	set_player_cor(modelPtr, 0, 20, 160); 	/* set player 1's position in play area */
	set_player_old_cor(modelPtr, 0, 0, 0);
	set_player_alive(modelPtr, 0, 0); 	/* set player 1's alive state to true */

	for(i = 0; i < 6; i++){
		generate_enemy_cor(modelPtr,i);

		/*set_enemy_cor(modelPtr, i, 556, i*52);*/
		set_enemy_old_cor(modelPtr, i, 0, 0); /*just set to something that isn't null*/
	}	
}

/** set_score: Used to set the score of a given model.  
 * 			   It takes a pointer to a model and changes it's score 
 * 			   value to the given value.
 * 
 * @param: modelPtr 
 * 		   A pointer to an object of the Model structure type.
 
 * @param: value
 * 		   A UINT16 type. It is the value to set the given models score to.
 * 
 * @return: none
 * 
 */
void set_score(struct Model *modelPtr, UINT16 value) {
	modelPtr->score = value;
}

/** get_score: Returns the current value of a given models score.
 * 			   It takes a pointer to a model and returns its score.
 * 
 * @param: modelPtr 
 * 		   A pointer to an object of the Model structure type.
 * 
 * @return: A UINT16 value.
 * 
 */
UINT16 get_score(struct Model *modelPtr) {
	return modelPtr->score;
}

void set_player_move_requested(struct Model *modelPtr, UINT16 player, UINT8 request) {
	modelPtr->players[player].move_requested = request;
}

UINT8 get_player_move_requested(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].move_requested;
}

void set_player_move_requested_direction(struct Model *modelPtr, UINT16 player, UINT8 direction) {
	modelPtr->players[player].move_requested_direction = direction;
}

UINT8 get_player_move_requested_direction(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].move_requested_direction;
}

void set_player_cor(struct Model *modelPtr, UINT16 player, UINT16 x, UINT16 y) {
	modelPtr->players[player].posX = x;
	modelPtr->players[player].posY = y;
}

UINT16 get_player_posX(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].posX;
}

UINT16 get_player_posY(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].posY;
}

void set_player_old_cor(struct Model *modelPtr, UINT16 player, UINT16 x, UINT16 y) {
	modelPtr->players[player].old_posX = x;
	modelPtr->players[player].old_posY = y;
}

UINT16 get_player_old_posX(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].old_posX;
}

UINT16 get_player_old_posY(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].old_posY;
}

void set_player_deltaX(struct Model *modelPtr, UINT16 player, UINT16 deltaX) {
	modelPtr->players[player].deltaX = deltaX;
}

UINT16 get_player_deltaX(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].deltaX;
}

void set_player_deltaY(struct Model *modelPtr, UINT16 player, UINT16 deltaY) {
	modelPtr->players[player].deltaY = deltaY;
}

UINT16 get_player_deltaY(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].deltaY;
}

void set_player_alive(struct Model *modelPtr, UINT16 player, UINT8 alive) {
	modelPtr->players[player].alive = alive;
}

UINT8 get_player_alive(struct Model *modelPtr, UINT16 player) {
	return modelPtr->players[player].alive;
}

void set_enemy_cor(struct Model *modelPtr, UINT16 enemy, UINT16 x, UINT16 y) {
	modelPtr->enemies[enemy].posX = x;
	modelPtr->enemies[enemy].posY = y;
}

UINT16 get_enemy_posX(struct Model *modelPtr, UINT16 enemy) {
	return modelPtr->enemies[enemy].posX;
}

UINT16 get_enemy_posY(struct Model *modelPtr, UINT16 enemy) {
	return modelPtr->enemies[enemy].posY;
}

void set_enemy_old_cor(struct Model *modelPtr, UINT16 enemy, UINT16 x, UINT16 y) {
	modelPtr->enemies[enemy].old_posX = x;
	modelPtr->enemies[enemy].old_posY = y;
}

UINT16 get_enemy_old_posX(struct Model *modelPtr, UINT16 enemy) {
	return modelPtr->enemies[enemy].old_posX;
}

UINT16 get_enemy_old_posY(struct Model *modelPtr, UINT16 enemy) {
	return modelPtr->enemies[enemy].old_posY;
}

/*
make a boolean array so a lane isn't occupied by more than one ship
*/
void generate_enemy_cor(struct Model *modelPtr, UINT16 enemy){
	int enemyY = 0;
	int r = rand() % 7;
	
	
	if(r == 0)
		enemyY = 0;
	else if(r == 1)
		enemyY = 52;
	else if(r == 2)
		enemyY = 104;
	else if(r == 3)
		enemyY = 156;
	else if(r == 4)
		enemyY = 208;
	else if(r == 5)
		enemyY = 260;
	else if(r == 6)
		enemyY = 312;
	else
		enemyY = 364;
	
	set_enemy_cor(modelPtr, enemy, 556, enemyY);

	}


void printModel(struct Model *modelPtr) {
	int i = 0;
	printf("Score: %u\n", get_score(modelPtr));
	for(i = 0; i < 6; i++){
		printf("lane for enemy: %i,%i",i,get_enemy_posY(modelPtr,i));
	}
	printf("\n");
	sleep(1);
	
}
