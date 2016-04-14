#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>

#include "bitmaps.h"

#include "klingon.h"

/*Don's plot bitmap*/
void plot_screen(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 80; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(80*i)+(80-k)];
         }
      }
   }

void plot_bitmap_32(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) {
   int i = 0,
      k = 0;

      for (i = 0; i < height; i++){
         for (k =0; k < 4; k++){
            *(base + ((y+i) * 80) + ((x >> 3) + k)) |= bitmap[(4*i)+(3-k)];
         }
      }
   }

void clear_area(UINT8 *base, int x, int y){
	int i = 0,
    k = 0;

    for (i = 0; i < 32; i++){
        for (k =0; k < 4; k++){
           *(base + ((y+i) * 80) + ((x >> 3) + k)) &= rocket_empty[(4*i)+(3-k)];
        }
    }
}

void splash_screen(UINT8 * base){
		clear_screen((long *) base);
		plot_screen(base, 0, 0, splash, 400);	
}

/*
play coords 50,127
exit coords 50,219

'w' and 's' to go up and down
'd' to make a selection until I get scancodes figured out
*/
int main() {
	/*char c;
	int start = 0;
	int selection = 0;*/
	
	
	int exit = 0;
	int currSelect = 0;
	char ch;
	
	UINT8 *base = (UINT8 *)get_video_base();
	
	install_vectors();

	
	splash_screen(base);
	plot_bitmap_32(base, 50, 127, rocket_right, 32);		
	
	while(!exit) {
		if(kbd_is_waiting()){
			ch = kbd_read_char();
			
			if(ch == 'w' && currSelect) {
				currSelect--;
				clear_area(base,50,219);
				plot_bitmap_32(base, 50, 127, rocket_right, 32);
			}
			else if(ch == 's' && !currSelect) {
				currSelect++;
				clear_area(base, 50, 127);
				plot_bitmap_32(base, 50, 219, rocket_right, 32);
			}
			else if(ch == 'd' && !currSelect) {
				play_klingon();
				splash_screen(base);
				plot_bitmap_32(base, 50, 127, rocket_right, 32);
			}
			else if(ch == 'd' && currSelect) {
				exit = 1;
			}
		}
	}
	
	
	
	
	
    /*
	while (!((c == 'd') && (selection%2 == 1))){
		c = kbd_read_char();
		if((c == 's') && (selection%2 == 0)){
			selection++;
			
		}
		if((c == 'w') && (selection%2 == 1)){
			selection++;
			
		}
		if((c == 'd') && (selection%2 == 0)){
			start = 1;
			play_klingon();
			splash_screen(base);
			plot_bitmap_32(base, 50, 127, rocket_right, 32);
		}
	}*/
	/*
	while(ch != 0x1B) { 
		if (kbd_is_waiting()) {
			ch = kbd_read_char();
			printf("%c\n",ch);
		}
	}*/
    
    
	remove_vectors();
	
	return 0;
	
}





