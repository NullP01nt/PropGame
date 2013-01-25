#include <propeller.h>

#include "menudraw.h"
#include "vga_text.h"
#include "pins.h"

volatile cursor_info cInfo;
char menuList[MAX_ENTRIES][13];

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
	cInfo.cursor_row--;
	if(cInfo.cursor_row < CSR_START_ROW) cInfo.cursor_row = CSR_START_ROW;
	redrawCursor();
}

void cursor_down() {
	cInfo.old_row = cInfo.cursor_row;
	cInfo.cursor_row++;
	if(cInfo.cursor_row > cInfo.row_limit[cInfo.cursor_col]) cInfo.cursor_row = cInfo.row_limit[cInfo.cursor_col];
	redrawCursor();
}

void cursor_switch_col() {
	int new_col = cInfo.cursor_col ? 0 : 1;
	if(cInfo.row_limit[new_col]>0) {
		cInfo.old_col = cInfo.cursor_col;
		cInfo.cursor_col = new_col;
		redrawCursor();
	}
}

void setStatusbar(char* text) {
	vgaText_setXY(0,STS_BAR_ROW);
	vgaText_print(text);
}
