#include <osbind.h>
#include "raster.h"
#include "p1_ship.h"
#include "p2_ship.h"

int main() {
	UINT8 *base = Physbase();

	clear_screen();
	print_num(base, 0, 0, 1);
	plot_bitmap_64_byte(base, 200,200,p2_ship,32);
	print_line(base, 100,100,400,323);
	
	return 0;
}