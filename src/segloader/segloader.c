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

#define BLANK_CHAR 0x20
#define CURSOR_CHAR	0xBB

#define CLR_ROW( x )	vgaText_setXY(0,x);vgaText_print("                              ");

#define COL_0_X 0
#define COL_1_X 14
#define ROW_MIN 1
#define ROW_MAX	12

uint8_t PAD_ONE;

char executables[24][13];
uint8_t fileCount = 0;
char* filePointer;

int csr_col = 0, old_col = 0;
int csr_row = ROW_MIN, old_row = ROW_MIN;

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

void redraw_cursor(void) {
	vgaText_setXY(old_col * 14, old_row);
	vgaText_out(BLANK_CHAR);
	if(csr_row < ROW_MIN) csr_row = ROW_MIN;
	if(csr_row > ROW_MAX) csr_row = ROW_MAX;
	vgaText_setXY(csr_col * 14, csr_row);
	vgaText_out(CURSOR_CHAR);
	filePointer = executables[(csr_row-1)+(csr_col*12)];
}

void drawScreen(void) {
	drawTitle();
	drawFileList();
	redraw_cursor();
}

void redrawScreen(void) {
	vgaText_out(0x00);
	drawScreen();
}

int main(int argc, char** argv) {
	InitGPadIO();
	waitcnt(CLKFREQ/1+CNT);
	vgaText_start(VGA_BASE_PIN);
	sleep(1);
	listExecutables();
	drawScreen();
	while(1) {
		readPads();
		//usleep(1500);
		if(PAD_ONE == 0xFF) {
			int i = 0;
			for(i = ROW_MIN; i <= ROW_MAX; i++) {
				CLR_ROW(i);
			}
			vgaText_setXY(0,6);
			vgaText_print("Gamepad 1 Disconnected!");
			vgaText_setXY(0,7);
			vgaText_print("Press B after connecting");
		} else if(PAD_ONE & BUTTON_START) {
			vgaText_setXY(1,1);
			vgaText_str("START PRESSED");
		} else if (PAD_ONE & BUTTON_B) {
			redrawScreen();
		} else if (PAD_ONE & BUTTON_A) {
			vgaText_setXY(6,13);
			vgaText_print(filePointer);	
		} else if (PAD_ONE & BUTTON_UP) {
			old_col = csr_col;
			old_row = csr_row;
			csr_row--;
			redraw_cursor();
		} else if (PAD_ONE & BUTTON_DOWN) {
			old_col = csr_col;
			old_row = csr_row;
			csr_row++;
			redraw_cursor();
		} else if (PAD_ONE & BUTTON_SELECT) {
			old_col = csr_col;
			old_row = csr_row;

			csr_col = csr_col ? 0 : 1;
			redraw_cursor();
		} 
		vgaText_setXY(0,13);
		vgaText_dec(csr_col ? COL_1_X : COL_0_X);
		vgaText_putchar(',');
		vgaText_dec(csr_row);
		waitcnt(CLKFREQ/6+CNT);
	}
	return 0;
}
