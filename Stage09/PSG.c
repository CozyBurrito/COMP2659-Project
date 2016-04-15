/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>

#include "PSG.h"
#include "globals.h"


void write_psg(int reg, UINT8 val) {
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	*PSG_reg_select = reg;
	*PSG_reg_write  = val;

}
				
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

void stop_sound() {
	write_psg(8, 0);
	write_psg(9, 0);
	write_psg(10, 0);
}