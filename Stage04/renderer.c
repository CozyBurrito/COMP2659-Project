#include <osbind.h>

#include "renderer.h"

void render_model(struct Model *modelPtr, UINT8 *base) {
	
	clear_screen();
	
	render_player(modelPtr, base, 0);
	
	render_line(base);
	
	render_score(modelPtr, base);
	
}

void render_player(struct Model *modelPtr, UINT8 *base, UINT16 player) {
	UINT16 player_posX;
	UINT16 player_posY;
	
	player_posX = get_player_posX(modelPtr, player);
	player_posY = get_player_posY(modelPtr, player);
	
	plot_bitmap_64_byte(base, player_posX, player_posY, empty, P1_SHIP_HEIGHT);
	plot_bitmap_64_byte(base, player_posX, player_posY, p1_ship, P1_SHIP_HEIGHT);
	
}

void render_line(UINT8 *base) {
	print_line(base,0,344,640,344);
}


void render_score(struct Model *modelPtr, UINT8 *base) {
	UINT16 score = get_score(modelPtr);
	print_num(base, 590, 370, score);
	
}