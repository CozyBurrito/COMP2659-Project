#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <linea.h>

#include "model.h"
#include "events.h"
#include "renderer.h"
#include "globals.h"

UINT8 buffer[35256];

UINT32 get_time();
void disable_cursor();

int main() {
	int i = 0;
	UINT8 *base = Physbase();
	UINT8 *base2 = buffer;
	
	UINT8 ch;
	UINT8 has_moved = 1;
	UINT8 switchBase = 0;
	UINT32 timeNow, timeThen;

	struct Model game;
	struct Model *gamePtr = &game;
	
	base2 += 256 - ((long)base2 & (long)0xFF);

	
	for(i = 0; i < NUM_ENEMIES; i++){
		set_active(gamePtr,i,0);
	}
	init_model(gamePtr);
	
	disable_cursor();
	Setscreen(-1, base2, -1);
	disable_cursor();
	Setscreen(-1, base, -1);
	
	timeNow = get_time();
	timeThen = timeNow + 70;
	srand(time(0));

	while(!game_over(gamePtr)) {
		
		/* Check if there is kbd input */
		if(kbd_is_waiting()) {
			ch = kbd_read_char();	
			request_player_move(gamePtr, 0, ch);
		}

		if(timeNow != get_time()) {
			
			if(timeNow >= timeThen) {
				update_score(gamePtr, 1);
				timeThen = timeNow + 70;
			}
			
			
			has_moved = move_player_ship(gamePtr, 0);
			
			for(i = 0; i < NUM_ENEMIES; i++) {
				move_enemy_ship(gamePtr, i);
				collision(gamePtr,i,0);
			}	
			
			
			if(switchBase) {
				Setscreen(-1, base2, -1);
				Vsync();
				render_model(gamePtr, base, has_moved);
				
			}
			else {
				Vsync();
				render_model(gamePtr, base2, has_moved);
			}
			
			
			switchBase = !switchBase;
			Setscreen(-1, base, -1);
			
		}
		
		
		
		timeNow = get_time();
	
	}
	
	return 0;
}

void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
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

