#include <osbind.h>

#include "renderer.h"

void render_model(struct Model *modelPtr, UINT8 *base) {
	
	clear_screen();
	
	render_player(modelPtr, base, 0);
	
	/*
	render_line();
	
	render_score();
	*/
}

void render_player(struct Model *modelPtr, UINT8 *base, UINT16 player) {
	UINT16 player_posX;
	UINT16 player_posY;
	
	player_posX = get_player_posX(modelPtr, player);
	player_posY = get_player_posY(modelPtr, player);
	
	plot_bitmap_64_byte(base, player_posX, player_posY, p1_ship, P1_SHIP_HEIGHT);
	
}