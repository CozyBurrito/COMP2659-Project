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
	UINT8 *base = (UINT8 *)get_video_base();

    install_vectors();

    render_splash_screen(base);
    render_rocket(base, 0);
    
	while(!exit) {
        
        /* Read a character from the keyboard if a key is pressed */
		if(kbd_is_waiting()) {
			input = kbd_read_char();
		}
        
        /* Either change selection, play the game, or quit the game */
        if(input == KBD_W && selection) {
			input = 0;
			selection = 0;
            render_rocket(base, 0);
        }
        else if (input == KBD_S && !selection) {
			selection = 1;
            render_rocket(base, 1);
			input = 0;
        }
        else if (input == KBD_D && !selection) {
			input = 0;
			play_klingon(base);
            render_splash_screen(base);
			render_rocket(base, 0);
        }
        else if (input == KBD_D && selection) {
            exit = true;
        }
        
	}
    
	clear_screen((long *)base);
	
    remove_vectors();	

	return 0;		
}






