#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cog.h>
#include <ctype.h>
#include <propeller.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sd.h>

#undef CALL_MOUNT
#undef SPINNERET_CARD
#undef PROP_BOE
#undef C3_CARD
#undef PARALLEL_SPI

#include "fileio.h"
#include "vga_text.h"
#include "gamepad.h"

uint8_t PAD_ONE;

char* executables[13];

extern _Driver _SimpleSerialDriver;
extern _Driver _FileDriver;

_Driver *_driverlist[] = {
	&_SimpleSerialDriver,
	&_FileDriver,
	NULL
};

int main(int argc, char** argv) {
	int curs_x=1, curs_y=1;
	int old_x=1, old_y=1;
	InitGPadIO();
	vgaText_start(16); // Start VGA on base 16
	waitcnt(CLKFREQ/1+CNT);
	listExecutables();
	while(1) {
		readPads();
		vgaText_out(0x00);
		usleep(250);
		old_x = curs_x;
		old_y = curs_y;
		if(PAD_ONE & BUTTON_START) {
			vgaText_setXY(1,0);
			vgaText_str("START PRESSED");
		} else if (PAD_ONE & BUTTON_UP) {
			curs_y--;
		} else if (PAD_ONE & BUTTON_DOWN) {
			curs_y++;
		} else if (PAD_ONE & BUTTON_LEFT) {
			curs_x--;
		} else if (PAD_ONE & BUTTON_RIGHT) {
			curs_x++;
		}
		if(curs_x<0) curs_x = 0;
		if(curs_x>=29) curs_x = 29;
		if(curs_y<0) curs_y = 0;
		if(curs_y>12) curs_y = 12;
		if(curs_x != old_x && curs_y != old_y) {
			vgaText_setXY(old_x,old_y);
			vgaText_out(0x20);
		}
		vgaText_setXY(curs_x,curs_y);
		vgaText_out(0xBB);
		//printf("%d\t%d\n",curs_x,curs_y);
		usleep(1000);
	}
	vgaText_print("Hello, Imara\n");
	vgaText_print("Hello, Xander\n");
	vgaText_print("--- PEX Files ---\n");
	listFilesByExt(NULL,"pex");
	vgaText_print("\n--- All Files ---\n");
	while(1);
	return 0;
}
