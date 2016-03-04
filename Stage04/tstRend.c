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
	
	render_model(gamePtr, base);
	
	return 0;
}