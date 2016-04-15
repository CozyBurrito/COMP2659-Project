/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#include <osbind.h>
#include "PSG.h"
/*
toggles channel A noise on
*/
void thruster()
{
	write_psg(7,0x36);
}
/*
toggles channel A noise off
*/
void stop_thruster()
{
	write_psg(7,0x3E);

}

/*
plays explosion sound effect
*/
void explosion()
{
	write_psg(6,0x1F);

	write_psg(7,0x07);
	
	write_psg(8,0x10);
	
	write_psg(9,0x10);
	
	write_psg(0xA,0x10);
	
	write_psg(0xC,0x38);

	write_psg(0xD,0x00);
}