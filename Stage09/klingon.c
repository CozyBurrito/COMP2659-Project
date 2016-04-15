/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <linea.h>
#include "music.h"
#include "klingon.h"

UINT8 buffer[35256];

struct Model game;
struct Model *gamePtr = &game;

int music_ticks = 0;
int score_ticks = 0;
int enemy_ticks = 0;
int render_request = 1;
UINT8 has_moved = 1; 

void play_klingon() {
	long old_ssp;
	Vector orig_vector;
	Vector main_vector;
	UINT8 ch;
	UINT8 switchBase = 0;
    
    UINT8 *base = (UINT8 *)get_video_base();
	UINT8 *base2 = buffer;

	base2 = (UINT8*)((UINT32)base2 + (256 - ((UINT32)base2) & 255));

	init_model(gamePtr);
	
	srand(time(0));
		
	start_music();

	while(!game_over(gamePtr)) {

	if(buffer_full()){
		ch = get_input();
		request_player_move(gamePtr, 0, ch);
	}
		if(render_request == 1) {
			if(switchBase) {
				render_model(gamePtr, base, has_moved);
				set_video_base((UINT16*)base);
			}
			else {
				render_model(gamePtr, base2, has_moved);
				set_video_base((UINT16*)base2);
			}
			
			switchBase = !switchBase;
			render_request = 0;
		}
		stop_thruster();
	}
	stop_music();

	explosion();	
	
	set_video_base((UINT16*)base);
}




