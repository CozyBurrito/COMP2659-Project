/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>

#include "ISRS.h"

Vector VBL_orig_vector;
Vector IKBD_orig_vector;

UINT8 head = 0;
UINT8 tail = 0;

UINT8 IKBD_buffer[256];

int music_ticks = 0;
int score_ticks = 0;
int enemy_ticks = 0;
int render_request = 1; 

unsigned char mse_button = 0xF8;
unsigned char mse_deltaX = 0x00;
unsigned char mse_deltaY = 0x00;

int mse_state = 0;

volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 


void do_VBL_ISR() {
	music_ticks++;
	if (update_music(music_ticks)){
		music_ticks = 0;
	}

	score_ticks++;

	enemy_ticks++;
	
	render_request = 1;
}

void do_IKBD_ISR(){
	UINT8 code = *(READER);
	
	if(!mse_state) {
		if((code & 0x80 ) != 0x80){ 
			IKBD_buffer[tail++] = code;
		}
		else if (code >= 0xF8){
			mse_button = code;
			mse_state--;
		}
	}
	else {
		if(mse_state < 0) {
			mse_deltaX = code;
			mse_state = 1;
		}
		else {
			mse_deltaY = code;
			mse_state--;
		}
	}
		
  *MFP &= 0xBF;
}

void install_vectors() {
    mask_interrupts();

	VBL_orig_vector = install_vector(VBL_ISR, vbl_isr);
    IKBD_orig_vector = install_vector(IKBD_ISR, ikbd_isr);
	
	unmask_interrupts();
}

void remove_vectors() {
    mask_interrupts();

	install_vector(VBL_ISR, VBL_orig_vector);
    install_vector(IKBD_ISR, IKBD_orig_vector);
	
	unmask_interrupts();
}

Vector install_vector(int num, Vector vector) {
	Vector original_vector;
	Vector *vectp = (Vector *)((long)num << 2);
    
	long old_ssp = Super(0);
    
	original_vector = *vectp;
	*vectp = vector;
	
    Super(old_ssp);
    
	return original_vector;
}

void mask_interrupts() {
    long old_ssp = Super(0);
    *IE &= 0xBF;
    Super(old_ssp);
}

void unmask_interrupts() {
    long old_ssp = Super(0);
    *IE |= 0x40;
    Super(old_ssp);
}


