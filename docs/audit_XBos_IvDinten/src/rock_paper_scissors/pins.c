#include <stdio.h>
#include <propeller.h>

#include "pins.h"

void pinOut(int pin, int value)
{
    uint32_t mask = 1 << pin;
    uint32_t data = (value & 1) << pin;
    OUTA = (OUTA & ~mask) | data;
}

uint8_t pinIn(int pin) {
	return (INA & (1<<pin)) ? 1 : 0;	
}
