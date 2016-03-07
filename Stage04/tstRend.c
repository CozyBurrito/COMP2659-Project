#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "model.h"
#include "renderer.h"
#include "globals.h"

int main() {
	
	UINT8 *base = Physbase();
	
	struct Model game;
	struct Model *gamePtr = &game;
	init_model(gamePtr);
	
	init_render(base);
	
	render_model(gamePtr, base);
	
	set_player_cor(gamePtr, 0, 200, 300);
	set_player_old_cor(gamePtr, 0, 20, 160);
	
	set_score(gamePtr, 25);
	
	render_model(gamePtr, base);


	return 0;
}