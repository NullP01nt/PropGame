#include <stdio.h>
#include <stdint.h>
#include <propeller.h>

#include "gamepad.h"
#include "vga_text.h"
#include "menudraw.h"

extern uint8_t PAD_ONE;

int main(int argc, char** argv) {
	initGPadIO();
	initScreen();
	while(1) {
		readPads();
		if (PAD_ONE & BUTTON_B) {
			setStatusbar("Button B Pressed");	
		} else if (PAD_ONE & BUTTON_UP) {
			cursor_up();
			setStatusbar("Button UP Pressed");	
		} else if (PAD_ONE & BUTTON_DOWN) {
			cursor_down();
			setStatusbar("Button DOWN Pressed");	
		} else if (PAD_ONE & BUTTON_SELECT) {
			cursor_switch_col();
			setStatusbar("Button SELECT Pressed");	
		} 
		vgaText_setXY(0,11);
		vgaText_bin(PAD_ONE,8);
		waitcnt(CLKFREQ/6+CNT);
	}
	return 0;
}
