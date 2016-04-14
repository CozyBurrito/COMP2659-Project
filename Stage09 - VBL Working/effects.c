/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#include <osbind.h>
#include "PSG.h"

/* 
Starts the thruster sound
*/
void thruster() {
	long old_ssp = Super(0);
	write_psg(7,0x36);
	Super(old_ssp);
}

/* 
Stops the thruster sound
*/
void stop_thruster()
{
	long old_ssp = Super(0);
	write_psg(7,0x3E);
	Super(old_ssp);
}

/* 
plays an explosion sound
*/
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