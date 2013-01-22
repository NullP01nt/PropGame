#ifndef __GBL_PINS_H
#define __GBL_PINS_H

#define GP_CLK		8
#define GP_LATCH	9
#define GP_D1		10
#define GP_D2		11

#define SPI_SCK		0
#define SPI_MOSI	1
#define SPI_MISO	2
#define SPI_SD_CS	3
#define SPI_SRAM_CS	4
#define SPI_VRAM_CS	5

void pinSet(int,int);

#endif
