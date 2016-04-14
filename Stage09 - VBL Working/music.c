#include <osbind.h>
#include "music.h"

static int j = 0;

UINT16 noteArray[] = {C_5,B_4,C_5,G_4,F_4,
	                  C_5,B_4,C_5,G_4,F_4,
					  C_5,B_4,C_5,D_5,F_5,
				   	  E_5,C_5,D_5,B_4,G_4,
					  E_5,C_5,D_5,B_4,G_4,
				      G_5,C_5,F_5,E_5,D_5,B_4,B_1
					  };

UINT16 timeArray[] = {54,54,56,56,56,
					  54,54,56,56,56,
					  54,54,54,60,60,
					  54,54,56,56,56,
					  54,54,56,56,56,
					  50,50,50,60,60,50,50
					  };
					  
void start_sound(){
	long old_ssp = Super(0);
	
	set_tone(0, C_5);
	enable_channel(0, 1, 0);
	set_volume(0, 11);
	
	Super(old_ssp);
}

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