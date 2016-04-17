/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>

#include "main.h"

int main() {
	bool exit = false;
	int selection = 0;
    UINT8 input;
	
	UINT32 *base = (UINT32 *)get_video_base();

    install_vectors();
	
	mse_enable = 1;
	
	clear_screen((long *)(UINT8 *)base);
	
	init_mouse(base);
	
    render_splash_screen((UINT8 *)base);
    render_rocket((UINT8 *)base, 0);
	
    
	while(!exit) {
        
		update_mouse(base);
		
         /* Read a character from the keyboard if a key is pressed  */
		if(kbd_is_waiting()) {
			input = kbd_read_char() >> 16;
		}
        
         /* Either change selection, play the game, or quit the game  */
        if((input == KBD_W || mouse_inBounds() == 1) && selection)  {
			input = 0;
			selection = 0;
            render_rocket((UINT8 *)base, 0);
        }
        else if ((input == KBD_S || (mouse_inBounds() == 2)) && !selection) {
			selection = 1;
            render_rocket((UINT8 *)base, 1);
			input = 0;
        }
        else if ((input == KBD_D || mse_click == 2) && !selection) {
			input = 0;

			mse_enable = 0;
			
			play_klingon((UINT8 *)base);

			mse_enable = 1;
			
            render_splash_screen((UINT8 *)base);
			render_rocket((UINT8 *)base, 0);
			init_mouse(base);
			
        }
        /* else if ((input == KBD_ESC || input == KBD_D || mse_click == 2) && selection) {
            exit = true;
        }*/
        
	}
	
    clear_kbd_buffer();
	
	clear_screen((long *)(UINT8 *)base);
	
    remove_vectors();	
	
	return 0;		
}

/* 0 = not in bounds, 1 = in bounds to "play", 2 = in bounds to "quit" */
UINT8 mouse_inBounds() {
	UINT8 inBounds = 0;
	
	if((mseX >= 85 && mseX <= 248) &&
		(mseY >= 120 && mseY <= 172)) 
		{
			inBounds = 1;
		}
	if ((mseX >= 85 && mseX <= 248) &&
		(mseY >= 206 && mseY <= 258))
		{
			inBounds = 2;
		}
		
	
	return inBounds;
}






