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

#include "fileio.h"
#include "vga_text.h"
#include "gamepad.h"

#define COL_0_X 0
#define COL_1_X 14
#define ROW_MIN 1
#define ROW_MAX	12

uint8_t PAD_ONE;

char* executables[24][13];
uint8_t fileCount = 0;

extern _Driver _SimpleSerialDriver;
extern _Driver _FileDriver;

_Driver *_driverlist[] = {
	&_SimpleSerialDriver,
	&_FileDriver,
	NULL
};

void drawTitle(void) {
	vgaText_setXY(6,0);
	vgaText_print("GameBlade Loader");
}

void drawFileList(void) {
	int txt_col=COL_0_X+1, txt_row=ROW_MIN;
	int file_index=0;
	for(file_index=0; file_index<fileCount; file_index++) {
		if(file_index == 12) {
			txt_col = COL_1_X+1;
			txt_row = ROW_MIN;
		}
		vgaText_setXY(txt_col,txt_row);
		vgaText_print(executables[file_index]);
		txt_row++;
	}
}

int main(int argc, char** argv) {
	int cursor_col = COL_0_X;
	int old_col = cursor_col;
	int cursor_row = ROW_MIN;
	int old_row = cursor_row;
	int redraw=1;
	InitGPadIO();
	waitcnt(CLKFREQ/1+CNT);
	vgaText_start(16); // Start VGA on base 16
	sleep(1);
	listExecutables();
	drawTitle();
	drawFileList();
	printf("Files: %d\n",fileCount);
	while(1) {
		readPads();
		usleep(1500);
		if(redraw==1) {
			vgaText_setXY(old_col,old_row);
			vgaText_out(0x20);
			vgaText_setXY(cursor_col,cursor_row);
			vgaText_out(0xBB);
			redraw=0;
		}
			if(PAD_ONE & BUTTON_START) {
				vgaText_setXY(1,1);
				vgaText_str("START PRESSED");
			} else if (PAD_ONE & BUTTON_B) {
				vgaText_out(0x00);
				drawTitle();
				drawFileList();
				redraw=1;	
			}else if (PAD_ONE & BUTTON_UP) {
				old_row = cursor_row;
				cursor_row--;
				redraw=1;
			} else if (PAD_ONE & BUTTON_DOWN) {
				old_row = cursor_row;
				cursor_row++;
				redraw=1;
			} else if (PAD_ONE & BUTTON_LEFT) {
				old_col = cursor_col;
				cursor_col = COL_0_X;
				redraw=1;
			} else if (PAD_ONE & BUTTON_RIGHT) {
				old_col = cursor_col;
				cursor_col = COL_1_X;
				redraw=1;
			}
			if(cursor_row < ROW_MIN) cursor_row = ROW_MIN;
			if(cursor_row > ROW_MAX) cursor_row = ROW_MAX;
		waitcnt(CLKFREQ/50+CNT);
	}
	vgaText_print("Hello, Imara\n");
	vgaText_print("Hello, Xander\n");
	vgaText_print("--- PEX Files ---\n");
	listFilesByExt(NULL,"pex");
	vgaText_print("\n--- All Files ---\n");
	while(1);
	return 0;
}
