#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <linea.h>

#include "model.h"
#include "events.h"
#include "renderer.h"
#include "globals.h"
#include "notes.h"

UINT8 buffer[35256];

UINT32 get_time();
void disable_cursor();

int main() {
	int i = 0;
	int j = 0;
	int musicCounter = 0;
	UINT8 *base = Physbase();
	UINT8 *base2 = buffer;
	
	UINT8 ch;
	UINT8 has_moved = 1;
	UINT8 switchBase = 0;
	
	UINT32 timeNow, timeThen;

	struct Model game;
	struct Model *gamePtr = &game;
	
	long old_ssp;
	
	base2 += 256 - ((long)base2 & (long)0xFF);

	init_model(gamePtr);
	
	disable_cursor();
	Setscreen(-1, base2, -1);
	disable_cursor();
	Setscreen(-1, base, -1);
	
	musicTime = get_time();
	timeNow = get_time();
	timeThen = timeNow + 70;
	
	start_sound(old_ssp);
	
	srand(time(0));
	
	while(!game_over(gamePtr)) {
		
		if(musicCounter < timeArray[j])
			musicCounter++;
		if(musicCounter == timeArray[j]){
			j++;
			musicCounter = 0;
			if(j > 31)
				j = 0;
		}
		old_ssp = Super(0);
		set_tone(0, noteArray[j]);
		Super(old_ssp);
		
		/* Check if there is kbd input */
		if(kbd_is_waiting()) {
			ch = kbd_read_char();	
			request_player_move(gamePtr, 0, ch);
		}

		/* If clock ticked */
		if(timeNow != get_time()) {
			
			/* Check if a second has passed */
			if(timeNow >= timeThen) {
				update_score(gamePtr, 1);
				timeThen = timeNow + 70;
			}
			
			/* Move player ship */
			has_moved = move_player_ship(gamePtr, 0);
			
			/* Move enemy ships and check collisions with player ship */
			for(i = 0; i < NUM_ENEMIES; i++) {
				move_enemy_ship(gamePtr, i);
				collision(gamePtr,i,0);
			}	
			
			
			/* Render the model with double buffering */
			if(switchBase) {
				render_model(gamePtr, base, has_moved);
				Setscreen(-1, base, -1);
			}
			else {
				render_model(gamePtr, base2, has_moved);
				Setscreen(-1, base2, -1);
			}
			
			Vsync();
			switchBase = !switchBase;
			
		}
		
		
		timeNow = get_time();
	
	}
	
	old_ssp = Super(0);
	stop_sound();
	Super(old_ssp);
	
	render_model(gamePtr, base, has_moved);
	Setscreen(-1, base, -1);
	Vsync();
	
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

