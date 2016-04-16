/**
Name: Don Hagen, Mohammad Hameed
Course: COMP 2659
Due Date: 15/04/2016
Instructor: ppospisil
*/

#ifndef GLOBALS_H
#define GLOBALS_H

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef UINT8 SCANCODE;


typedef enum { false, true } bool;


#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640


#define KBD_W       0x11
#define KBD_A       0x1E
#define KBD_S       0x1F
#define KBD_D       0x20

#define KBD_UP      0x48
#define KBD_DOWN    0x50
#define KBD_LEFT    0x4B
#define KBD_RIGHT   0x4D

#define KBD_ENTER   0x1C


#define SHIP_WIDTH 64
#define SHIP_HEIGHT 32


#define NUM_PLAYERS 1
#define NUM_ENEMIES 6


#define PLAYER_DX 8
#define PLAYER_DY 8


#define EMEMY_DX 8


#endif
