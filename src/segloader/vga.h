/*
############################################################################
# Written by Dave Hein
# Copyright (c) 2012 Parallax, Inc.
# MIT Licensed
############################################################################
*/

#ifndef __GBL_VGA_H
#define __GBL_VGA_H

#define bitsPerPixel      1
#define horizontalScaling 1
#define horizontalPixels  640

typedef struct VgaVarS {
    uint32_t directionState;
    uint32_t videoState;
    uint32_t frequencyState;
    uint32_t verticalScaling;
    uint32_t verticalPixels;
    uint32_t visibleScale;
    uint32_t invisibleScale;
    uint32_t horizontalLongs;
    uint32_t *colortable1;
    uint32_t *buffer1;
    uint32_t *pixelColorsAddress;
    uint32_t *syncIndicatorAddress;
} VgaVarT;

typedef struct ObjectS {
    int col;
    int prevcol;
    int row;
    int delcol;
    int delrow;
    uint32_t *object;
    int width;
    int height;
    int mass;
} ObjectT;

void initVGAIO();
void VGAStart(int pinGroup, int vertRes, int *newDisplayPointer, int *colorTable, int *pixelColours, int *syncIndicator);
void Step(void);
#endif
