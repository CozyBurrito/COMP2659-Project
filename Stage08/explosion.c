#include <osbind.h>
#include "explosion.h"
void explosion()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;

	long old_ssp = Super(0);

	*PSG_reg_select = 6;
	*PSG_reg_write  = 0x1F;

	*PSG_reg_select = 7;
	*PSG_reg_write  = 0x07;

	*PSG_reg_select = 8;
	*PSG_reg_write  = 0x10;
	
	*PSG_reg_select = 9;
	*PSG_reg_write  = 0x10;
	
	*PSG_reg_select = 0xA;
	*PSG_reg_write  = 0x10;
	
	*PSG_reg_select = 0xC;
	*PSG_reg_write  = 0x38;
	
	*PSG_reg_select = 0xD;
	*PSG_reg_write  = 0x00;

	Super(old_ssp);
}
