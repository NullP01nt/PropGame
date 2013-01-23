#ifndef __GBL_VGA_TEXT_H
#define __GBL_VGA_TEXT_H

#define CHAR_HEIGHT		11
#define CHAR_WIDTH		8

void PutCharImage(int, int, int, int, int, int);
void PutStringImage(int, int, char*, int, int, int);
#endif
