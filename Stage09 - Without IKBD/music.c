/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>

#include "music.h"

static int j = 0;

/* Contains the notes for a given song as defined in music.h */
UINT16 noteArray[] = {  C_5, B_4, C_5, G_4,
                        F_4, C_5, B_4, C_5,
                        G_4, F_4, C_5, B_4,
                        C_5, D_5, F_5, E_5,
                        C_5, D_5, B_4, G_4,
                        E_5, C_5, D_5, B_4,
                        G_4, G_5, C_5, F_5,
                        E_5, D_5, B_4, B_1
                     };
                     
/* Duration of each note in noteArray */
UINT16 timeArray[] = {  54, 54, 56, 56, 
                        56, 54, 54, 56, 
                        56, 56, 54, 54, 
                        54, 60, 60, 54,
                        54, 56, 56, 56,
                        54, 54, 56, 56,
                        56, 50, 50, 50,
                        60, 60, 50, 50
					  };
                      
/* 
Purpose: Start the music by playing the first note and enabling the channel
*/
void start_music(){
	long old_ssp = Super(0);
    
	set_tone(0, C_5);
	enable_channel(0, 1, 0);
	set_volume(0, 11);
    
	Super(old_ssp);
}

/* 
Purpose: Stops all sounds, serves as a high-level function
*/
void stop_music(){
	long old_ssp = Super(0);
    
	stop_sound();
    
	Super(old_ssp);
}

/*
Purpose: The function determines if it's time to play the
        next note of the song or continue playing the current one
Param: time since last note was played
Return: true = note was updated, false = no change in note
*/
bool update_music(UINT32 time_elapsed){
	bool updated = false;
	
	if(time_elapsed >= timeArray[j]){
		j++;
		updated = true;
	}
	
	if(j > 31) {
		j = 0;
	}
	
	set_tone(0, noteArray[j]);
	
	return updated;
}