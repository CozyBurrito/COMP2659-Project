/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>

#include "PSG.h"

/* 
Purpose: Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper routine to be
         used by the other functions in this module.
Param: reg = register to write to 
       cal = value to write in register
*/
void write_psg(int reg, UINT8 val) {
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	*PSG_reg_select = reg;
	*PSG_reg_write  = val;

}

/* 
Purpose: Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C) with the given
         12-bit tuning.
Param: channel = channel to write to, 0 = a, 1 = b, 2 = c
       tuning = coarse and fine tuning to set
*/		
void set_tone(int channel, int tuning) {
	if(channel == 0) {
		write_psg(0, (UINT8) tuning);
		write_psg(1, (UINT8) (tuning >> 8));
	}
	else if(channel == 1) {
		write_psg(2, (UINT8) tuning);
		write_psg(3, (UINT8) (tuning >> 8));
	}
	else if(channel == 2) {
		write_psg(4, (UINT8) tuning);
		write_psg(5, (UINT8) (tuning >> 8));
	}
}

/* 
Purpose: Loads the volume register for the given channel.
Param: channel = channel to write to, 0 = a, 1 = b, 2 = c
       volume = volume from 0 to 11
*/		
void set_volume(int channel, int volume) {
	if(channel == 0) {
		write_psg(8, (UINT8) volume);
	}
	else if(channel == 1) {
		write_psg(9, (UINT8) volume);
	}
	else {
		write_psg(10, (UINT8) volume);
	}
	
}

/* 
Purpose: Turns the given channel’s tone/noise signals on/off (0=off, 1=on). only 1 of tone or noise can be on at the same time
Param: channel : channel to write to, 0 = a, 1 = b, 2 = c
       tone_on : 0 = enable tone, 1 = disable tone
       noise_on : 0 = enable noise, 1 = disable noise
*/		
void enable_channel(int channel, int tone_on, int noise_on) {	
	if(channel == 0) {
		if(tone_on) {
			write_psg(7, 0x3E);
		}
		else if (noise_on) {
			write_psg(7, 0x37);
		}
		
	}
	else if (channel == 1) {
		if(tone_on) {
			write_psg(7, 0x3D);
		}
		else if (noise_on) {
			write_psg(7, 0x2F);
		}
		
	}
	else if (channel == 2) {
		if(tone_on) {
			write_psg(7, 0x3B);
		}
		else if (noise_on) {
			write_psg(7, 0x1F);
		}
	}
}

/* 
Purpose: Stops all sounds by setting all channels volumes to 0
*/	
void stop_sound() {
	write_psg(8, 0);
	write_psg(9, 0);
	write_psg(10, 0);
}