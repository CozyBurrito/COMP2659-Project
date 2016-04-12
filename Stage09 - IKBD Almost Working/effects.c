#include <osbind.h>
#include "PSG.h"

void thruster() {
	long old_ssp = Super(0);
	write_psg(7,0x36);
	Super(old_ssp);
}

void stop_thruster()
{
	long old_ssp = Super(0);
	write_psg(7,0x3E);
	Super(old_ssp);
}

void explosion()
{
	long old_ssp = Super(0);
	write_psg(6,0x1F);

	write_psg(7,0x07);
	
	write_psg(8,0x10);
	
	write_psg(9,0x10);
	
	write_psg(0xA,0x10);
	
	write_psg(0xC,0x38);

	write_psg(0xD,0x00);
	Super(old_ssp);
	
}