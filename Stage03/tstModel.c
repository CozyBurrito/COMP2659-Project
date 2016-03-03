#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "events.h"
#include "model.h"

int main() {
	UINT8 *base = Physbase();
	
	struct Model game;
	struct Model *gamePtr = &game;
	
	char ch;

	init_model(gamePtr);
	printModel(gamePtr);

	while(!game_over(gamePtr)) {
		ch = Cnecin();
		
		if(ch == ' ') {
			move_player_ship(gamePtr, 0);
			printModel(gamePtr);
		} else {
			request_player_pos_change(gamePtr, 0, ch);
		}
		
	}

	return 0;
}
