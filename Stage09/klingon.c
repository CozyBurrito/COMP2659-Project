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

#include "klingon.h"

Vector install_vector(int num, Vector vector);

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
	
	orig_vector = install_vector(VBL, vbl_isr);
	
	old_ssp = Super(0);
	start_sound();
	Super(old_ssp);

	while(!game_over(gamePtr)) {
	/*if the buffer containts something, read it and put it in ch*/	
	/*complete the move request*/
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
		
		old_ssp = Super(0);
		/*Thruster was turned on in the move function, now that it has been
		  completed, turn it off before we loop back*/
		stop_thruster();
		Super(old_ssp);
	}
	/*loop exit means the player has lost the game, play explosion sound here*/
	old_ssp = Super(0);
	stop_sound();
	explosion();
	Super(old_ssp);
	
	/*restore the vector*/
	install_vector(VBL, orig_vector);
	/*draw the correct version of the model to the screen so the game isn't left hanging in the wrong state*/
	render_model(gamePtr, base, has_moved);
	set_video_base((UINT16*)base);
    
}

Vector install_vector(int num, Vector vector) {
	Vector orig;
	Vector *vectp = (Vector *)((long)num << 2);
	long old_ssp = Super(0);
	
	orig = *vectp;
	*vectp = vector;
	
	Super(old_ssp);
	return orig;
}

/*
VBL ISR timers
*/
void do_VBL_ISR() {
	int i = 0;
	
	music_ticks++;
	if (update_music(music_ticks)){
		music_ticks = 0;
	}

	score_ticks++;
	if(score_ticks >= 70){
		update_score(gamePtr, 1);
		score_ticks = 0;
	}
	
	has_moved = move_player_ship(gamePtr, 0);
	if(has_moved){
		thruster();
	}
	
	enemy_ticks++;
	for(i = 0; i < NUM_ENEMIES && enemy_ticks >= 10; i++) {
		move_enemy_ship(gamePtr, i);
		collision(gamePtr,i,0);
	}
	if(enemy_ticks >= 10) {
		enemy_ticks = 0;
	}
	
	render_request = 1;
}


