/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include "klingon.h"
#include "globals.h"
#include "ISR.h"

unsigned char buffer[256];

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
	/*move this to ISR.c and make a function*/
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
		/*make game loop when player dies, go back to menu*/
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






