#ifndef __GBL_PINS_H
#define __GBL_PINS_H

// Define GamePad pins
#define GP_CLK			11
#define GP_LATCH		10
#define GP_D1			9
#define GP_D2			8

// Define SPI pins
#define SPI_SCK			0
#define SPI_MOSI		1
#define SPI_MISO		2
#define SPI_SD_CS		3
#define SPI_SRAM_CS		4
#define SPI_VRAM_CS		5

#define VGA_BASE_PIN	16

// PIN LOGIC LEVELS
#define HIGH			1
#define LOW				0

void	pinOut(int,int);
uint8_t	pinIn(int);

#endif
