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
typedef unsigned char SCANCODE;
typedef unsigned char UBYTE;
typedef enum { false, true } bool;
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640

#define UP 0x11
#define DOWN 0x1F
#define LEFT 0x1E
#define RIGHT 0x20

#define SHIP_WIDTH 64
#define SHIP_HEIGHT 32

#define NUM_PLAYERS 1
#define NUM_ENEMIES 6

#define PLAYER_DX 8
#define PLAYER_DY 8

#define EMEMY_DX 8

#define DELAY 70

#define KBD_ISR 70

#endif