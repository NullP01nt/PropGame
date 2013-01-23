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

#include "pins.h"
#include "fileio.h"
#include "vga_text.h"
#include "gamepad.h"

#define COL_0_X 0
#define COL_1_X 14
#define ROW_MIN 1
#define ROW_MAX	12

uint8_t PAD_ONE;

char executables[24][13];
uint8_t fileCount = 0;
char* filePointer;

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
	int file_index;
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
	int csr_col = 0, old_col = 0;
	int csr_row = ROW_MIN, old_row = csr_row;
	int csr_redraw = 1;
	InitGPadIO();
	waitcnt(CLKFREQ/1+CNT);
	vgaText_start(VGA_BASE_BIN);
	sleep(1);
	listExecutables();
	drawTitle();
	drawFileList();
	while(1) {
		readPads();
		//usleep(1500);
		if(csr_redraw == 1) {
			vgaText_setXY(old_col * COL_1_X, old_row);
			vgaText_out(0x20);
			vgaText_setXY(csr_col * COL_1_X, csr_row);
			vgaText_out(0xBB);
			filePointer = executables[(csr_row-1)+(csr_col*12)];
			csr_redraw = 0;
		}
			if(PAD_ONE & BUTTON_START) {
				vgaText_setXY(1,1);
				vgaText_str("START PRESSED");
			} else if (PAD_ONE & BUTTON_B) {
				vgaText_out(0x00);
				drawTitle();
				drawFileList();
				csr_redraw=1;	
			} else if (PAD_ONE & BUTTON_A) {
				vgaText_setXY(6,13);
				vgaText_print(filePointer);	
			} else if (PAD_ONE & BUTTON_UP) {
				old_row = csr_row;
				csr_row--;
				csr_redraw=1;
			} else if (PAD_ONE & BUTTON_DOWN) {
				old_row = csr_row;
				csr_row++;
				csr_redraw=1;
			} else if (PAD_ONE & BUTTON_LEFT) {
				old_col = csr_col;
				csr_col = 0;
				csr_redraw=1;
			} else if (PAD_ONE & BUTTON_RIGHT) {
				old_col = csr_col;
				csr_col = 1;
				csr_redraw=1;
			}
			if(csr_row < ROW_MIN) csr_row = ROW_MIN;
			if(csr_row > ROW_MAX) csr_row = ROW_MAX;
			vgaText_setXY(0,13);
			vgaText_dec(csr_col ? COL_1_X : COL_0_X);
			vgaText_putchar(',');
			vgaText_dec(csr_row);
		waitcnt(CLKFREQ/50+CNT);
	}
	return 0;
}
