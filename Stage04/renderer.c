#include <osbind.h>

#include "renderer.h"

void init_render(UINT8 *base) {
	clear_screen();
	render_line(base);
	
}

void render_model(struct Model *modelPtr, UINT8 *base) {
	
	render_ship(modelPtr, base, 0, 0);
	
	render_ship(modelPtr, base, 1, 0);
	
	render_score(modelPtr, base);
	
}

void render_ship(struct Model *modelPtr, UINT8 *base, UINT8 ship, UINT16 ship_num) {
	UINT16 ship_posX;
	UINT16 ship_posY;
	UINT16 ship_old_posX;
	UINT16 ship_old_posY;
	
	if(ship) {
		ship_posX = get_player_posX(modelPtr, ship_num);
		ship_posY = get_player_posY(modelPtr, ship_num);
	
		ship_old_posX = get_player_old_posX(modelPtr, ship_num);
		ship_old_posY = get_player_old_posY(modelPtr, ship_num);
	}
	else {
		ship_posX = get_enemy_posX(modelPtr, ship_num);
		ship_posY = get_enemy_posY(modelPtr, ship_num);
	
		ship_old_posX = get_enemy_old_posX(modelPtr, ship_num);
		ship_old_posY = get_enemy_old_posY(modelPtr, ship_num);
		
	}
	
	if(ship_posX != ship_old_posX && ship_posY != ship_old_posY) {
		if(ship) {
			plot_bitmap_64_byte(base, ship_old_posX, ship_old_posY, empty, SHIP_HEIGHT);
			plot_bitmap_64_byte(base, ship_posX, ship_posY, p1_ship, SHIP_HEIGHT);
		}
		else {
			plot_bitmap_64_byte(base, ship_old_posX, ship_old_posY, empty, SHIP_HEIGHT);
			plot_bitmap_64_byte(base, ship_posX, ship_posY, en_ship, SHIP_HEIGHT);
		}
		
	}
	
}

void render_line(UINT8 *base) {
	print_line(base,0,344,640,344);
}

void render_score(struct Model *modelPtr, UINT8 *base) {
	UINT16 score = get_score(modelPtr);
	
	print_clr_num(base, 590, 370);
	print_num(base, 590, 370, score);
	
}