/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include "music.h"

static int j = 0;
/*contains the notes for a given song as defined in music.h*/
UINT16 noteArray[] = {C_5,B_4,C_5,G_4,F_4,
	                  C_5,B_4,C_5,G_4,F_4,
					  C_5,B_4,C_5,D_5,F_5,
				   	  E_5,C_5,D_5,B_4,G_4,
					  E_5,C_5,D_5,B_4,G_4,
				      G_5,C_5,F_5,E_5,D_5,B_4,B_1
					  };
/*duration of each note in noteArray*/
UINT16 timeArray[] = {54,54,56,56,56,
					  54,54,56,56,56,
					  54,54,54,60,60,
					  54,54,56,56,56,
					  54,54,56,56,56,
					  50,50,50,60,60,50,50
					  };
/*
sets up sound registers IOT begin playing sounds*/
void start_music(){
	long old_ssp = Super(0);
	set_tone(0, C_5);
	enable_channel(0, 1, 0);
	set_volume(0, 11);
	Super(old_ssp);
}

void stop_music(){
	long old_ssp = Super(0);
	stop_sound();
	Super(old_ssp);

}

/*Given a time, the function determines if it's time to play the
next note of the song or continue playing the current one*/
UINT8 update_music(UINT32 time_elapsed){
	UINT8 updated = 0;
	
	if(time_elapsed >= timeArray[j]){
		j++;
		updated = 1;
	}
	
	if(j > 31) {
		j = 0;
	}
	
	set_tone(0,noteArray[j]);
	
	return updated;
}