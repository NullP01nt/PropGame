/*
############################################################################
# Written by Dave Hein
# Copyright (c) 2012 Parallax, Inc.
# MIT Licensed
############################################################################
*/
#include <stdio.h>
#include <string.h>
#include "vga_draw.h"

#define ncol 640
#define nrow 480

extern unsigned char *tilemap;
extern int tiles[16*256];
volatile int lastindex = 0;
volatile int background = 0;
volatile int lockindex = 0;

inline int getindex(uint8_t *ptr) {
	int index = *ptr;
	int index1 = index;

	if(index > lockindex) return index;

	if(lastindex == 255) return 0;

	index = ++lastindex;
	memcpy(&tiles[index<<4], &tiles[index1<<4], 64);
	*ptr = index;

	return index;
}

inline void drawdotfast(int col, int row, int color)
{
    int tilenum, index, shift;

    tilenum = (col >> 4) + (row >> 4) * (ncol >> 4);
    if (!(index = getindex(&tilemap[tilenum]))) return;
    index <<= 4;
    index += row & 15;
    shift = (col & 15) << 1;
    tiles[index] = (tiles[index] & ~(3 << shift)) | (color << shift);
}

/*inline void drawdot(int col, int row, int color)
{
    int tilenum, index, shift;

    if (col < 0 || col >= ncol || row < 0 || row >= nrow) return;

    if (color < 0 || color >= COLOR_MAX) return;

    color &= 3;

    tilenum = (col >> 4) + (row >> 4) * (ncol >> 4);
    if (!(index = getindex(&tilemap[tilenum]))) return;
    index *= 16;
    index += row & 15;
    shift = (col & 15) << 1;
    tiles[index] = (tiles[index] & ~(3 << shift)) | (color << shift);
}*/

/*
+--------------------------------------------------------------------
|  TERMS OF USE: MIT License
+--------------------------------------------------------------------
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
+------------------------------------------------------------------
*/

