#include <propeller.h>

#include "menudraw.h"
#include "vga_text.h"
#include "pins.h"

volatile cursor_info cInfo;
char menuList[MAX_ENTRIES][MAX_ENTRY_LENGTH];

void initCursor() {
	cInfo.cursor_col = 0;
	cInfo.cursor_row = CSR_START_ROW;
	cInfo.old_col = cInfo.cursor_col;
	cInfo.old_row = cInfo.cursor_row;
	cInfo.row_limit[0] = 1;
	cInfo.row_limit[1] = 0;
}

void initScreen() {
	initCursor();
	vgaText_start(VGA_BASE_PIN);
	drawScreen();
}

void drawList() {
	int i=0,j=0;
	int txt_col=1,txt_row=CSR_START_ROW;
	if(fileCount > 0) {
		if(fileCount <= (MAX_ENTRIES>>1)) {
			cInfo.row_limit[0] = fileCount+1;
			cInfo.row_limit[1] = 0;
		} else {
			cInfo.row_limit[0] = (MAX_ENTRIES>>1);
			cInfo.row_limit[1] = (fileCount-(MAX_ENTRIES>>1))+1;
		}
		for(i=0; i<fileCount; i++) {
			if(i==(MAX_ENTRIES>>1)) {
				txt_col = 15;
				txt_row = CSR_START_ROW;
			}
			vgaText_setXY(txt_col,txt_row);
			/*for(j=0; j<8; j++) {
				vgaText_putchar(menuList[i][j]);
			}*/
			vgaText_print(menuList[i]);
			txt_row++;
		}
	}
}

void drawScreen() {
	vgaText_setXY(TITLE_COL, TITLE_ROW);
	vgaText_print(TITLE_TEXT);
	drawCursor();
}

void drawCursor() {
	vgaText_setXY(cInfo.cursor_col*COL_1_X, cInfo.cursor_row);
	vgaText_out(CSR_CHAR);
}

void redrawCursor() {
	vgaText_setXY(cInfo.old_col*COL_1_X, cInfo.old_row);
	vgaText_out(BLANK_CHAR);
	drawCursor();
}

void cursor_up() {
	cInfo.old_row = cInfo.cursor_row;
	cInfo.old_col = cInfo.cursor_col;
	cInfo.cursor_row--;
	if(cInfo.cursor_row < CSR_START_ROW) cInfo.cursor_row = CSR_START_ROW;
	redrawCursor();
}

void cursor_down() {
	cInfo.old_row = cInfo.cursor_row;
	cInfo.old_col = cInfo.cursor_col;
	cInfo.cursor_row++;
	if(cInfo.cursor_row > cInfo.row_limit[cInfo.cursor_col]) cInfo.cursor_row = cInfo.row_limit[cInfo.cursor_col];
	redrawCursor();
}

void cursor_switch_col() {
	int new_col = cInfo.cursor_col ? 0 : 1;
	int new_row = cInfo.cursor_row;
	if(cInfo.row_limit[new_col]>0) {
		if(cInfo.cursor_row > cInfo.row_limit[new_col]) new_row = cInfo.row_limit[new_col];
		cInfo.old_row = cInfo.cursor_row;
		cInfo.old_col = cInfo.cursor_col;
		cInfo.cursor_col = new_col;
		cInfo.cursor_row = new_row;
		redrawCursor();
	}
}

void setStatusbar(char* text) {
	CLR_ROW(STS_BAR_ROW);
	vgaText_setXY(0,STS_BAR_ROW);
	vgaText_print(text);
}

int getCursorIndex() {
	return ((cInfo.cursor_row-CSR_START_ROW)+(cInfo.cursor_col*11));
}
