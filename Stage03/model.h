#ifndef MODEL_H
#define MODEL_H

#include "types.h"

#define NUM_PLAYERS 1
#define NUM_ENEMIES 1

#define PLAYER_DX 8
#define PLAYER_DY 8

#define EMEMY_DX 8

/** @struct playerShip
 *	@brief This structure is the player's ship
 *
 *  @var playerShip::posX 
 *  Member 'posX' is an integer value representing the X coordinate
 *
 *  @var playerShip::posY 
 *  Member 'posY' is an integer value representing the Y coordinate
 * 	
 * 	@var playerShip:: deltaX
 *  Member 'deltaX' is an integer value representing the change in X
 *
 *  @var playerShip:: deltaY
 *  Member 'deltaY' is an integer value representing the change in Y
 * 	
 *  @var playerShip::alive 
 *  Member 'alive' is an integer value represented by 0 = alive, 1 = dead
 */
typedef struct {
	UINT16 posX;
	UINT16 posY;
	
	UINT16 deltaX;
	UINT16 deltaY;
	
	UINT8 alive;
	
} playerShip;


/** @struct enemyShip
 *	@brief This structure is the enemies's ship
 *
 *  @var playerShip::posX 
 *  Member 'posX' is an integer value representing the X coordinate
 *
 *  @var playerShip::posY 
 *  Member 'posY' is an integer value representing the Y coordinate
 * 
 * 	@var playerShip:: deltaX
 *  Member 'deltaX' is an integer value representing the change in X
 */
typedef struct {
	UINT16 posX;
	UINT16 posY;
	
	UINT16 deltaX;
	
} enemyShip;


/** @struct Model
 *	@brief This structure is the game model
 *
 *  @var Model::score
 *  Member 'score' is an integer value representing the game score
 *
 *  @var Model::players
 *  Member 'players' is an array of playerShips that represents the players.
 *  0 = Player 1, 1 = Player 2
 *
 *  @var Model::enemies
 *  Member 'enemies' is an array of enemyShips that represents the enemies
 *  0 = Enemy 1, 1 = Enemy 2, ... 
 */
struct Model {
	UINT16 score;
	
	UINT8 player_move_requested;
	char player_move_requested_direction;
	
	playerShip players[NUM_PLAYERS];
	
	enemyShip enemies[NUM_ENEMIES];

};

void init_model(struct Model *modelPtr);

void set_score(struct Model *modelPtr, UINT16 value);
UINT16 get_score(struct Model *modelPtr);

void set_player_move_requested(struct Model *modelPtr, UINT8 request);
UINT8 get_player_move_requested(struct Model *modelPtr);

void set_player_move_requested_direction(struct Model *modelPtr, char direction);
char get_player_move_requested_direction(struct Model *modelPtr);

void set_player_cor(struct Model *modelPtr, UINT16 player, UINT16 x, UINT16 y);
UINT16 get_player_posX(struct Model *modelPtr, UINT16 player);
UINT16 get_player_posY(struct Model *modelPtr, UINT16 player);

void set_player_deltaX(struct Model *modelPtr, UINT16 player, UINT16 deltaX);
UINT16 get_player_deltaX(struct Model *modelPtr, UINT16 player);
void set_player_deltaY(struct Model *modelPtr, UINT16 player, UINT16 deltaY);
UINT16 get_player_deltaY(struct Model *modelPtr, UINT16 player);

void request_player_pos_change(struct Model *modelPtr, UINT16 player, char direction);

void set_player_alive(struct Model *modelPtr, UINT16 player, UINT8 alive);
UINT8 get_player_alive(struct Model *modelPtr, UINT16 player);

void set_enemy_cor(struct Model *modelPtr, UINT16 enemy, UINT16 x, UINT16 y);
UINT16 get_enemy_posX(struct Model *modelPtr, UINT16 enemy);
UINT16 get_enemy_posY(struct Model *modelPtr, UINT16 enemy);

void printModel(struct Model *modelPtr);
	
#endif