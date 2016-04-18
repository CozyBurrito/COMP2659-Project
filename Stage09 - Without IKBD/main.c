/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

/*
 * This is the main starting point for the game.
 * It starts up the splash screen and handles its events
 * Also it installs the required vectors
 *
 */

#include <osbind.h>

#include "main.h"

int main() {
	bool exit = false;
	int selection = 0;
    UINT8 input;
	
	UINT32 *base = (UINT32 *)get_video_base();  /* only call, casted to UINT16 and UINT8 when needed */

    install_vectors();
	
	mse_enable = 0;     /* enable the mouse to be rendered */
	
	clear_screen((long *)base);
	
	/* init_mouse(base); */   /* initialize the starting X and Y of mouse, and save background, then plot mouse */
	
    
    /* render the splash screen to main base */
    render_splash_screen((UINT8 *)base);
    render_rocket((UINT8 *)base, 0);
	
   
    /* Loop the splash screen until "exit" option is selected */
	while(!exit) {
        
        
		/* update_mouse(base);*/ /* update the mouse, then try to render it (renders every ~1/70th second)*/ 
		
        /* Read a character from the keyboard if a key is pressed */
		if(kbd_is_waiting()) {
			input = kbd_read_char() >> 16;
		}
        
        /* Either change selection, play the game, or quit the game */
        if((input == KBD_W || mouse_inBounds() == 1) && selection)  {
			input = 0;
			selection = 0;
            render_rocket((UINT8 *)base, 0);
        }
        else if ((input == KBD_S || (mouse_inBounds() == 2)) && !selection) {
			input = 0;
            selection = 1;
            render_rocket((UINT8 *)base, 1);
        }
        else if ((input == KBD_D || mse_click == 2) && !selection) {
			input = 0;

			mse_enable = 0;
			
			play_klingon((UINT8 *)base);    /* Start the game */

			mse_enable = 0;
			
            /* render the splash screen again, and reset the mouse */
            render_splash_screen((UINT8 *)base);
			render_rocket((UINT8 *)base, 0);
			/* init_mouse(base); */
			
        }
        else if ((input == KBD_ESC || input == KBD_D || mse_click == 2) && selection) {
            exit = true;
        }
        
	}
	
    clear_kbd_buffer();
	
	clear_screen((long *)(UINT8 *)base);
	
    remove_vectors();  

	return 0;		
}

/* Purpose: Check if the current mouse position 
            is in bounds to one of the selection options
   
   Return: 0 = not in bounds 
           1 = in bounds to "play"
           2 = in bounds to "quit"   
*/
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






