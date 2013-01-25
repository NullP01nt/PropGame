#include <stdio.h>
#include <propeller.h>

#define MP_MODE

#include "gamepad.h"

volatile uint8_t PAD_ONE;
volatile uint8_t PAD_TWO;

int main(int argc, char** argv) {
	initGPadIO();
	initScreen();
	while(1) {
		readPads();

	}
	return 0;
}
