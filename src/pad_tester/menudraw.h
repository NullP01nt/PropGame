#ifndef __GBL_MENU_DRAW__H
#define __GBL_MENU_DRAW__H

#include "vga_text.h"

#define MAX_ENTRIES			22
#define	MAX_ENTRY_LENGTH	12
#define COL_WIDTH			30
#define ROW_HEIGHT			14
#define BLANK_CHAR			0x20
#define CSR_CHAR			0xBB
#define CSR_START_ROW		1
#define TITLE_ROW			0
#define TITLE_TEXT			"GameBlade Loader"
#define TITLE_LEN			16
#define TITLE_COL			(COL_WIDTH-TITLE_LEN)>>1
#define COL_1_X				14
#define STS_BAR_ROW			12
#define CLR_ROW( x )		vgaText_setXY(0,x);vgaText_print("                              ");
#define clearStatusbar()	CLR_ROW(STS_BAR_ROW);

typedef struct cursor_t {
	uint8_t	cursor_col;
	uint8_t	cursor_row;
	uint8_t old_col;
	uint8_t old_row;
	uint8_t row_limit[2];
} cursor_info;

void initCursor(void);
void initScreen(void);

void drawList(void);
void drawScreen(void);

void drawCursor(void);
void redrawCursor(void);
void cursor_up(void);
void cursor_down(void);
void cursor_switch_col(void);

void setStatusbar(char*);
int getCursorIndex(void);
#endif
