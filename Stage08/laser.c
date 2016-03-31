#include <osbind.h>
#include "laser.h"

void laser()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	long old_ssp = Super(0);
    /*figure out how to have two channels playing at the same time.
	  Can't make channel b stop playing static. Channel b got stuck on forever 
	  after this function was called. 
	*/
	Super(old_ssp);
}