#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "model.h"
#include "events.h"
#include "renderer.h"
#include "globals.h"

UINT32 get_time();
void us(struct Model *gamePtr);

int main() {
	
	UINT8 *base = Physbase();
	
	UINT8 ch;
	UINT8 has_moved = 1;
	UINT8 sync = 0;
	UINT32 time;
	
	struct Model game;
	struct Model *gamePtr = &game;
	
	init_model(gamePtr);
	
	init_render(base);
	render_model(gamePtr, base, has_moved);
	
	time = get_time();

	while(!game_over(gamePtr)) {
		
		/* Check if there is kbd input */
		if(Cconis()) {
			ch = Cnecin();	
			request_player_move(gamePtr, 0, ch);
		}
		
		if(time != get_time()) {
			
			if(get_time() % 2 == 0) {
				us(gamePtr);
			}
			
			has_moved = move_player_ship(gamePtr, 0);
			move_enemy_ship(gamePtr, 0);
			render_model(gamePtr, base, has_moved);
		}
		
		time = get_time();
		
	
	}

	return 0;
}

void us(struct Model *gamePtr) {
	gamePtr->score += 1;
}

UINT32 get_time() {
	UINT32 *timer = 0x462;
	UINT32 time;
	UINT32 old_ssp;
	
	old_ssp = Super(0);
	
	time = *timer;
	
	Super(old_ssp);
	
	return time;
}

