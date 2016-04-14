#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <linea.h>

#include "klingon.h"

UINT8 buffer[35256];

struct Model game;
struct Model *gamePtr = &game;

int music_ticks = 0;
int score_ticks = 0;
int enemy_ticks = 0;
int render_request = 1;
UINT8 has_moved = 1; 

Vector orig_vector_vbl;
Vector orig_vector_ikbd;

unsigned char *IKBD_RDR = 0xFFFFFC02;
char *ascii_tbl = 0xFFFE829C;

unsigned char IKBD_buffer[256];
unsigned char head = 0; /* indexes into buffer array */
unsigned char tail = 0;
unsigned char key;
int fill = 256;

void play_klingon() {
	int i;
	
	UINT8 ch;
	UINT8 switchBase = 0;
    
    UINT8 *base = (UINT8 *)get_video_base();
	UINT8 *base2 = buffer;

	base2 = (UINT8*)((UINT32)base2 + (256 - ((UINT32)base2) & 255));

	init_model(gamePtr);
	
	srand(time(0));
	
	start_sound();
	
	while(!game_over(gamePtr)) {
		
		/* Check if there is kbd input */
		if(kbd_is_waiting()) {
			ch = kbd_read_char();	
			request_player_move(gamePtr, 0, ch);
		}

		if(score_ticks >= 70) {
			update_score(gamePtr, 1);
			score_ticks = 0;
		}
		
		has_moved = move_player_ship(gamePtr, 0);
		if(has_moved) {
			thruster();
		}
		
		for(i = 0; i < NUM_ENEMIES && enemy_ticks >= 3; i++) {
			move_enemy_ship(gamePtr, i);
			collision(gamePtr,i,0);
		}
		if(enemy_ticks >= 3){
			enemy_ticks = 0;
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

	stop_sound();

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

void do_VBL_ISR() {
	music_ticks++;
	if (update_music(music_ticks)){
		music_ticks = 0;
	}

	score_ticks++;
	
	enemy_ticks++;
	
	has_moved = 1;
	
	render_request = 1;
}

void do_IKBD_ISR() {
	/* Turn off MIDI */
	/* Check if IKBD is asserting IRQ */
	/* Mask all interrupts */
	int orig_ipl = set_ipl(7);
	
    key = *IKBD_RDR;
    
    if((!(key & 0x80)) && (fill > 0)) {    /* If it's a make code, save it */
		IKBD_buffer[tail] = *IKBD_RDR;
		tail++;
		fill--;
    }
    
	set_ipl(orig_ipl);
	/* Unmask all interrupts */
	
}

long kbd_is_waiting() {
	return fill < 256;
}

char kbd_read_char() {
    char ret = 0;
    
	while(fill == 256);
	
	if(fill < 256){
		ret = *(ascii_tbl + IKBD_buffer[head]);
		head++;
		fill++;
	}
    
    return ret;
}

void install_vectors() {
	orig_vector_vbl = install_vector(VBL, vbl_isr);
	orig_vector_ikbd = install_vector(IKBD, ikbd_isr);
}

void remove_vectors() {
	install_vector(VBL, orig_vector_vbl);
	install_vector(IKBD, orig_vector_ikbd);
}

