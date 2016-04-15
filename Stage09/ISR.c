#include "ISR.h"

unsigned char head, tail;

volatile   		unsigned char *const CTRL		= 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 

void do_kbd_isr(){
  unsigned char code = *(READER);
  if((code & 0x80 ) != 0x80){ 
	buffer[tail++] = code;
  }  
  *MFP &= 0xBF;
}

Vector install_vector(int num, Vector vector){
	Vector original_vector;
	Vector *vectp = (Vector *)((long)num << 2);
	long old_ssp = Super(0);
	
	original_vector = *vectp;
	*vectp = vector;
	
	Super(old_ssp);
	return original_vector;
}

/*
VBL ISR timers
move some stuff to play_klingon
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
		start_thruster();
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