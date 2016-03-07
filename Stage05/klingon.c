#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "model.h"
#include "events.h"
#include "renderer.h"
#include "globals.h"

int main() {
	
	UINT8 *base = Physbase();
	
	UINT8 ch;
	UINT8 has_moved = 1;
	UINT8 sync = 0;
	
	struct Model game;
	struct Model *gamePtr = &game;
	
	init_model(gamePtr);
	
	init_render(base);
	render_model(gamePtr, base, has_moved);

	while(!game_over(gamePtr)) {
		
		/* Check if there is kbd input */
		if(Cconis()) {
			ch = Cnecin();	/* if there is kdb input, read it */
			
			request_player_move(gamePtr, 0, ch);	/* Check char and request a move if valid */
			
			sync = 1;

		}
		
		/* Check if there is a clock tick */
		if(sync) {
			has_moved = move_player_ship(gamePtr, 0);	/* Move the ship if a move was requested */
			collision(gamePtr,0,0);
			move_enemy_ship(gamePtr, 0);
			collision(gamePtr,0,0);
			render_model(gamePtr, base, has_moved); 		/* Print the status of the model */
			
			sync = 0;
		}
			
	}

	return 0;
}