#include <osbind.h>

typedef unsigned char UINT8;

void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();

unsigned int arr[] = {0x00D6, 0x00E2, 0x00D6, 0x011D, 0x0140};

int main() {
	int j = 0; 
	unsigned long timeNow;
	
	long old_ssp = Super(0);
	
	unsigned long *timer = 0x462;
	
	set_tone(0, 248);
	enable_channel(0, 1, 0);
	set_volume(0, 11);
	
	timeNow = *timer;
	
	while (!Cconis()) {		/* tone now playing, await key */
	
		set_tone(0, arr[j]);
		j++;
		while(timeNow + 35 >= *timer);
		timeNow = *timer;

		if(j > 4) {
			j = 0;
		}
	}
	
	stop_sound();
	Super(old_ssp);
	return 0;
}

void write_psg(int reg, UINT8 val) {
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	

	/* add SUPER CALL */
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






