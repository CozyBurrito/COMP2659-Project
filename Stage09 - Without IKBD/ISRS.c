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

int render_mouse = 0;

int mseX;
int mseY;

int old_mseX;
int old_mseY;

int mse_click;
int mse_enable;

volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 

/*
Purpose: Execute these things when VBL_ISR is invoked
         Called by vbl_isr
*/
void do_VBL_ISR() {
	music_ticks++;
	if (update_music(music_ticks)){
		music_ticks = 0;
	}

	score_ticks++;

	enemy_ticks++;
		
	if (mse_enable == 1) {
		render_mouse = 1;
	}
	
	render_request = 1;
}

/*
Purpose: Execute these things when IKBD_ISR is invoked
         Called by ikbd_isr
*/
void do_IKBD_ISR(){
	UINT8 code = *(READER);
	
	if(mse_state == 0) {        /* If it's the first packet */
		if (code >= 0xF8){      /* If it's the mouse head packet */
			mse_button = code;
			mse_state = 1;
		}
		else if((code & 0x80 ) == 0x00){    /* If it's a make code add it to the buffer */
			IKBD_buffer[tail++] = code;
		}
		
	}
	else if(mse_state == 1) {   /* If it's delta X */
		mse_deltaX = code;
		mse_state = 2;
	}
	else if(mse_state == 2) {   /* If it's delta Y */
		mse_deltaY = code;
		mse_state = 0;
	}
	else {                      /* Here just to make sure */
		mse_state = 0;
	}
		
  /* Clear bit #6 in in-service B register */
  *MFP &= 0xBF;
}

/*
Purpose: Initialize mouse settings, and draw it 
*/
void init_mouse(UINT32 *base) {
	mseX = 320;
	mseY = 200;
	
	old_mseX = mseX;
	old_mseY = mseY;
	
	mse_click = 0;
	
	save_mouse_bkgd(base, mseX, mseY); 
	plot_mouse((UINT16 *)base, mseX, mseY, mouse_cursor);
}

/*
Purpose: Update the mouse values and draw mouse if requested
*/
void update_mouse(UINT32 *base) {
	
    /* Set new mouse values */
	mseX += (int)((char)mse_deltaX);
	mseY += (int)((char)mse_deltaY);

    /* Check for screen bounds */
	if(mseX < 0) {
		mseX = 0;
	}
	else if(mseX > 628) {
		mseX = 628;
	}
	
	if(mseY < 0) {
		mseY = 0;
	}
	else if(mseY > 378) {
		mseY = 378;
	}

	mse_deltaX = 0;
	mse_deltaY = 0;
		

    /* Set mouse click values */
    if(mse_button == 0xF8) {
		mse_click = 0;
	}
	else if(mse_button == 0xF9) {
		mse_click = 1;
	}
	else if(mse_button == 0xFA) {
		mse_click = 2;
	}
    else if(mse_button == 0xFB) {
		mse_click = 3;
	}

    /* If requested to render mouse, then draw it. Hooked up to vbl timer */
	if(render_mouse == 1) {
		restore_mouse_bkgd(base, old_mseX, old_mseY);
		save_mouse_bkgd(base, mseX, mseY);
		plot_mouse((UINT16 *)base, mseX, mseY, mouse_cursor);
		
		old_mseX = mseX;
		old_mseY = mseY;
		
		render_mouse = 0;
	}	
	
}

/*
Purpose: Install all vectors needed
*/
void install_vectors() {
    mask_interrupts();

	VBL_orig_vector = install_vector(VBL_ISR, vbl_isr);
    /* IKBD_orig_vector = install_vector(IKBD_ISR, ikbd_isr); */
	
	unmask_interrupts();
}

/*
Purpose: UnInstall all vectors needed
*/
void remove_vectors() {
    mask_interrupts();

	install_vector(VBL_ISR, VBL_orig_vector);
    /* install_vector(IKBD_ISR, IKBD_orig_vector); */
	
	unmask_interrupts();
}

/*
Purpose: Install single vector
         (From In Class Lab)
*/
Vector install_vector(int num, Vector vector) {
	Vector original_vector;
	Vector *vectp = (Vector *)((long)num << 2);
    
	long old_ssp = Super(0);
    
	original_vector = *vectp;
	*vectp = vector;
	
    Super(old_ssp);
    
	return original_vector;
}

/*
Purpose: Turn off interrupts by masking them
*/
void mask_interrupts() {
    long old_ssp = Super(0);
    *IE &= 0xBF;
    Super(old_ssp);
}

/*
Purpose: Turn on interrupts by unmasking them
*/
void unmask_interrupts() {
    long old_ssp = Super(0);
    *IE |= 0x40;
    Super(old_ssp);
}