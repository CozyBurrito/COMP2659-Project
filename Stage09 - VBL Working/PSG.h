/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/
#ifndef PSG_H
#define PSG_H
#include "globals.h"

#define C_1 0x0D5D
#define C_2 0x06AE
#define C_3 0x0357
#define C_4 0x01AC
#define C_5 0x00D6
#define C_6 0x006B
#define C_7 0x0035
#define C_8 0x001B

#define C_SHARP_1 0x0C9C
#define C_SHARP_2 0x064E
#define C_SHARP_3 0x0327
#define C_SHARP_4 0x0194
#define C_SHARP_5 0x00CA
#define C_SHARP_6 0x0065
#define C_SHARP_7 0x0032
#define C_SHARP_8 0x0019

#define D_1 0x0BE7
#define D_2 0x05F4
#define D_3 0x02FA
#define D_4 0x017D
#define D_5 0x00BE
#define D_6 0x005F
#define D_7 0x0030
#define D_8 0x0018

#define D_SHARP_1 0x0B3C
#define D_SHARP_2 0x059E
#define D_SHARP_3 0x02CF
#define D_SHARP_4 0x0168
#define D_SHARP_5 0x00B4
#define D_SHARP_6 0x005A
#define D_SHARP_7 0x002D
#define D_SHARP_8 0x0016

#define E_1 0x0A9B
#define E_2 0x054D
#define E_3 0x02A7
#define E_4 0x0153
#define E_5 0x00AA
#define E_6 0x0055
#define E_7 0x002A
#define E_8 0x0015

#define F_1 0x0A02
#define F_2 0x0501
#define F_3 0x0281
#define F_4 0x0140
#define F_5 0x00A0
#define F_6 0x0050
#define F_7 0x0028
#define F_8 0x0014

#define F_SHARP_1 0x0973
#define F_SHARP_2 0x04B9
#define F_SHARP_3 0x025D
#define F_SHARP_4 0x012E
#define F_SHARP_5 0x0097
#define F_SHARP_6 0x004C
#define F_SHARP_7 0x0026
#define F_SHARP_8 0x0013

#define G_1 0x08EB
#define G_2 0x0475
#define G_3 0x023B
#define G_4 0x011D
#define G_5 0x008F
#define G_6 0x0047
#define G_7 0x0024
#define G_8 0x0012

#define G_SHARP_1 0x086B
#define G_SHARP_2 0x0435
#define G_SHARP_3 0x021B
#define G_SHARP_4 0x010D
#define G_SHARP_5 0x0087
#define G_SHARP_6 0x0043
#define G_SHARP_7 0x0022
#define G_SHARP_8 0x0011

#define A_1 0x07F2
#define A_2 0x03F9
#define A_3 0x01FC
#define A_4 0x00FE
#define A_5 0x007F
#define A_6 0x0040
#define A_7 0x0020
#define A_8 0x0010

#define A_SHARP_1 0x0780
#define A_SHARP_2 0x03C0
#define A_SHARP_3 0x01E0
#define A_SHARP_4 0x00F0
#define A_SHARP_5 0x0078
#define A_SHARP_6 0x003C
#define A_SHARP_7 0x001E
#define A_SHARP_8 0x000F

#define B_1 0x0714
#define B_2 0x038A
#define B_3 0x01C5
#define B_4 0x00E2
#define B_5 0x0071
#define B_6 0x0039
#define B_7 0x001C
#define B_8 0x000E

void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();

#endif