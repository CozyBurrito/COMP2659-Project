#include <osbind.h>
#include "laser.h"

void thruster()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	long old_ssp = Super(0);
       *PSG_reg_select = 7;    		/* enable channel A on mixer */
	*PSG_reg_write = 0x36;
	
	Super(old_ssp);
}

void stop_thruster()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	
	long old_ssp = Super(0);
	
	*PSG_reg_select = 7;   
    *PSG_reg_write  = 0x3E;
	
	Super(old_ssp);
}