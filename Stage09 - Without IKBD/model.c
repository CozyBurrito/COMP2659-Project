/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "model.h"

/* 
Purpose: Used to initialize the values of a given model.  
  		 It takes a pointer to a model and changes it's values 
 		 to set values, instead of having to call all of the
  	 	 functions individually.
Param: A pointer to the model struct
 */
void init_model(struct Model *modelPtr) {	
	int i;
	
	set_score(modelPtr, 0); 	/* initialize score to 0 */
	
	set_player_move_requested(modelPtr, 0, 0);  /* Set move requested to off */
	
	set_player_deltaX(modelPtr, 0, 8);  /* Set player speeds */
	set_player_deltaY(modelPtr, 0, 8);
	
	set_player_cor(modelPtr, 0, 20, 160); 	/* set player 1's position in play area */
	set_player_alive(modelPtr, 0, 0); 	/* set player 1's alive state to true */

	for(i = 0; i < NUM_ENEMIES; i++) {  /* Generate all enemies initial values */
		generate_enemy(modelPtr, i);
	}
	
}

/*
 * Rest of functions are getter's and setter's for all parameters in the structs in .h file 
 */
void set_score(struct Model *modelPtr, UINT16 value) {
	modelPtr->score = value;
}

UINT16 get_score(struct Model *modelPtr) {
	return modelPtr->score;
}

void update_score(struct Model *modelPtr, UINT16 value) {
	modelPtr->score += value;
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

/* 
Purpose: Generate an enemies initial values, randomly
Param: Pointer to model 
       the enemy to initialize
*/
void generate_enemy(struct Model *modelPtr, UINT16 enemy){
	UINT16 new_enemy_deltaX;
	UINT16 new_enemyY;
	
	new_enemy_deltaX = (rand() % 32) + 4;
	set_enemy_deltaX(modelPtr, enemy, new_enemy_deltaX);
	
	new_enemyY = rand() % 312;
	set_enemy_cor(modelPtr, enemy, 568, new_enemyY);
}	

void set_enemy_deltaX(struct Model *modelPtr, UINT16 enemy, UINT16 deltaX) {
	modelPtr->enemies[enemy].deltaX = deltaX;
}

UINT16 get_enemy_deltaX(struct Model *modelPtr, UINT16 enemy) {
	return modelPtr->enemies[enemy].deltaX;
}

void set_active(struct Model *modelPtr, UINT16 enemy, UINT16 active){
	modelPtr->enemies[enemy].active = active;
}

UINT16 get_active(struct Model *modelPtr, UINT16 enemy){
	return modelPtr->enemies[enemy].active;
}

/* 
Purpose: Mainly for testing, prints some of the models state
Param: Pointer to model
*/
void printModel(struct Model *modelPtr) {
	int i = 0;
    
	printf("Score: %u\n", get_score(modelPtr));
    
	for(i = 0; i < NUM_ENEMIES; i++){
		printf("lane for enemy: %i,%i",i,get_enemy_posY(modelPtr,i));
	}
	printf("\n");
    
	
}
