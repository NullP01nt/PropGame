#include <stdio.h>
#include <stdint.h>
#include <propeller.h>

#include "gamepad.h"
#include "pins.h"

#ifndef MP_MODE
#define SP_MODE
#endif

uint8_t PAD_ONE;
#ifdef MP_MODE
#undef SP_MODE
uint8_t PAD_TWO;
#endif

void initGPadIO(void) {
	#ifdef MP_MODE
	DIRA &= ~((1<<GP_D1)|(1<<GP_D2));		// Set GP_D1 and GP_D2 as INPUT
	#else // SP_MODE is defined
	DIRA &= ~((1<<GP_D1));					// Set GP_D1 as INPUT
	#endif
	DIRA |= ((1<<GP_CLK)|(1<<GP_LATCH));		// Set GP_CLK and GP_LATCH as OUTPUT

	pinOut(GP_LATCH,HIGH);
}

void readPads(void) {
	PAD_ONE = readButtons(GP_D1);
	#ifdef MP_MODE
	PAD_TWO = readButtons(GP_D2);
	#endif
}

uint8_t readButtons(int srcPin) {
	int i = 0;
	pinOut(GP_LATCH, LOW);
	pinOut(GP_CLK, 	LOW);
	uint8_t pad_vector = 0;
	uint8_t input = 0;
	for(i = PAD_BIT_LENGTH; i>0; i--) {
		input = (INA & (1<<srcPin)) ? 0 : 1;
		pad_vector |= (input<<(PAD_BIT_LENGTH-i));
		pinOut(GP_CLK, HIGH);
		waitcnt(500+CNT);
		pinOut(GP_CLK, LOW);
	}
	pinOut(GP_LATCH, HIGH);
	return pad_vector;
}
