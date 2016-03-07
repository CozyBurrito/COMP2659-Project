#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "events.h"

int main() {
	UINT8 *base = Physbase();
	
	struct Model game;
	struct Model *gamePtr = &game;
	
	UINT8 ch;
	UINT8 sync = 0;

	init_model(gamePtr);
	printModel(gamePtr);

	while(!game_over(gamePtr)) {
		
		/* Check if there is kbd input */
		if(Cconis()) {
			ch = Cnecin();	/* if there is kdb input, read it */
			
			request_player_move(gamePtr, 0, ch);	/* Check char and request a move if valid */
			
			if (ch == ' ') {	/* Check if it's a clock tick */
				sync = 1;
			}

		}
		
		/* Check if there is a clock tick */
		if(sync) {
			move_player_ship(gamePtr, 0);	/* Move the ship if a move was requested */
			collision(gamePtr, 0,0);
			move_enemy_ship(gamePtr, 0);
			collision(gamePtr, 0,0);
			/*
			update_score(gamePtr);
			*/
			printModel(gamePtr); 		/* Print the status of the model */
			
			sync = 0;
		}
			
	}

	return 0;
}
