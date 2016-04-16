/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>
#include <stdlib.h>
#include <time.h>

#include "klingon.h"

UINT8 buffer[35256];
	
struct Model game;
struct Model *gamePtr = &game;

void play_klingon(UINT8 *base) {	
	UINT8 input;
    UINT16 i = 0;
	bool switch_base = false;
    bool has_moved = false;
   
    /* Make buffer 256-byte aligned */
	UINT8 *base2 = buffer;
	base2 = (UINT8*)((UINT32)base2 + (256 - ((UINT32)base2) & 255));

    /* Initialize the game and create a seed for random generation */
	init_model(gamePtr);
	srand(time(0));
	
    /* Start the background music for the game */
	start_music();

    /* Main game loop, keep playing the game until the player dies */
	while(!game_over(gamePtr)) {

        /* Check if there as a keypress, if so, then check if it's a valid key and request model to be updated */
        if(kbd_is_waiting()){
            input = kbd_read_char() >> 16;
            request_player_move(gamePtr, 0, input);
        }
        
        /* Check if a second has passed, if so then update the score by 1 */
        if(score_ticks >= 70){
            update_score(gamePtr, 1);
            score_ticks = 0;
        }
        
        /* Try to move player's ship, if moved then start the thruster sound effect */
        if(move_player_ship(gamePtr, 0)){
            start_thruster();
        }
        
        /* Move each enemy and check collision if 3/70th of a second has passed */
        for(i = 0; i < NUM_ENEMIES && enemy_ticks >= 3; i++) {
            move_enemy_ship(gamePtr, i);
            collision(gamePtr,i,0);
        }
        if(enemy_ticks >= 3) {
            enemy_ticks = 0;
        }
        
        /* If there was a request to render the current state of the model, uses double buffering */
		if(render_request) {
			if(switch_base) {
				render_model(gamePtr, base, has_moved);
				set_video_base((UINT16*)base);
			}
			else {
				render_model(gamePtr, base2, has_moved);
				set_video_base((UINT16*)base2);
			}
			
			switch_base = !switch_base;
			render_request = false;
		}
        
        /* Stop the sound of the thruster, placed here since timing is good */
		stop_thruster();
	}
    
    /* Once the game is over, stop the music and play an explosion sound */
	stop_music();
	explosion();	
	
    /* Set the video base back to it's original before returning */
	set_video_base((UINT16*)base);
}




