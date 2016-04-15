/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include <stdlib.h>
#include <time.h>
#include <linea.h>
#include "bitmaps.h"
#include "klingon.h"
#include "globals.h"

unsigned char buffer[256];
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

unsigned char get_input(){
	unsigned char key;
	long old_ssp = Super(0);
	*IE &= 0xBF;
	Super(old_ssp);
	
	key = buffer[head++];
	
	old_ssp = Super(0);
	*IE |= 0x40;
	Super(old_ssp);
	return key;
}

bool buffer_full(){
	return head!=tail;
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

/*Don's plot bitmap, won't work with the bitmaps we shuffled up (ships)*/
void plot_screen(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 80; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(80*i)+(80-k)];
         }
      }
   }
   
/*Don's plot bitmap used to make the title screen selector move*/
/*This should be made into a neater function that can be passed a bitmap and values*/
void plot_bitmap_32(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 4; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(4*i)+(3-k)];
         }
      }
   }

/*these plot functions could be combined, no time. They work.*/
void clear_area(UINT8 *base, int x, int y){
	int i = 0,
    k = 0;

    for (i = 0; i < 32; i++){
        for (k =0; k < 4; k++){
           *(base + ((y+i) * 80) + ((x >> 3) + k)) &= rocket_empty[(4*i)+(3-k)];
        }
    }
}

/*function to draw the menu to the screen*/
void splash_screen(UINT8 * base){
		clear_screen((long *) base);
		plot_screen(base, 0, 0, splash, 400);	
}

/*uses scancodes for data from keyboard to keep operations down*/
int main() {
	unsigned char c;
	int start = 0;
	int selection = 0;
	long old_ssp = Super(0);
	Vector main_vector;
	UINT8 *base;
	
	/*wrap in function*/
	/*disable interrupts*/ 
	*IE &= 0xBF;
	Super(old_ssp);
	
	/*install vector*/
	main_vector = install_vector(KBD_ISR, kbd_isr);
	
	/*reenable interrupts*/
	old_ssp = Super(0);
	*IE |= 0x40;
	Super(old_ssp);
	
	
	base = get_video_base();
	splash_screen(base);
    plot_bitmap_32(base, 50, 127, rocket_right, 32);
	while(!start){
		
		if(buffer_full())
			c = get_input();
		
		if((c == 0x1f) && (selection%2 == 0)){
			selection++;
			clear_area(base, 50, 127);
			plot_bitmap_32(base, 50, 219, rocket_right, 32);
		}
		if((c == 0x11) && (selection%2 == 1)){
			selection++;
			clear_area(base,50,219);
			plot_bitmap_32(base, 50, 127, rocket_right, 32);
		}
		if((c == 0x1C) && (selection%2 == 0)){
			start = 1;
			play_klingon();
		}
		if((c == 0x1C) && (selection%2 == 1)){
			/*wrap in function*/
			/*disable interrupts*/
			old_ssp = Super(0);
			*IE &= 0xBF;
			Super(old_ssp);
	
			/*install vector*/
			install_vector(KBD_ISR, main_vector);
	
			/*reenable interrupts*/
			old_ssp = Super(0);
			*IE |= 0x40;
			Super(old_ssp);		

			return 0;
		}
	}
	
	/*wrap in function*/
	/*disable interrupts*/
	old_ssp = Super(0);
	*IE &= 0xBF;
	Super(old_ssp);
	
	/*install vector*/
	install_vector(KBD_ISR, main_vector);
	
	/*reenable interrupts*/
	old_ssp = Super(0);
	*IE |= 0x40;
	Super(old_ssp);		

	return 0;		
}






