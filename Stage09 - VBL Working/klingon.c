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
int mouse_count = 0;

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
	
	render_request = 1;
}

void do_IKBD_ISR() {
	/* Turn off MIDI */
	/* Check if IKBD is asserting IRQ */
	/* Mask all interrupts */
    UINT8 key = *IKBD_RDR;
	
	if(mouse_count == 0)
	{	
		if(!(key >= 0xF8))
		{
			 if(!(key & 0x80)) {    /* If it's a make code, save it */
				IKBD_buffer[tail] = key;
				tail++;
			}
		}
		else
		{
			mouse_count = 2;
		}
	}
	else
	{
		mouse_count --;
	}
	
}

UINT8 kbd_is_waiting() {
	/*return head != tail;*/
    return Cconis();
}

UINT8 kbd_read_char() {
    /*UINT8 ret = 0;
	
	if(tail != head) {
		ret = IKBD_buffer[head];
		head++;
		return ret;
	}
	
    return -1;*/
    
    return Cnecin();
}

void install_vectors() {
	orig_vector_vbl = install_vector(VBL, vbl_isr);
	/*orig_vector_ikbd = install_vector(IKBD, ikbd_isr);*/
}

void remove_vectors() {
	install_vector(VBL, orig_vector_vbl);
	/*install_vector(IKBD, orig_vector_ikbd);*/
}

