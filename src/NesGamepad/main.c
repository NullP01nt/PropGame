#include <stdio.h>
#include <stdlib.h>
#include <propeller.h>

// Pin numbers
#define CLOCK   4
#define LATCH   5
#define DATA1   6
#define DATA2   7
#define BITS    8

// Direction types
#define OUTPUT  1
#define INPUT   0

#define HIGH    1
#define LOW     0

// Button values
#define BTN_RIGHT   (1<<7)
#define BTN_LEFT    (1<<6)
#define BTN_DOWN    (1<<5)
#define BTN_UP      (1<<4)
#define BTN_START   (1<<3)
#define BTN_SELECT  (1<<2)
#define BTN_A       (1<<1)
#define BTN_B       (1<<0)

void pinSet(int,int);
unsigned char buttons(void);
int init_gamepad(void);

unsigned char P1_BUTTONS;
unsigned char P2_BUTTONS;

// if(P1_BUTTONS && (BTN_START | BTN_SELECT))

int main()
{
    printf("Hello world!\n");
    init_gamepad();
    return 0;
}

int init_gamepad()
{
    DIRA &= ~((1<<DATA1)|(1<<DATA2));   // DATA1 en DATA2 is INPUT
    DIRA |= ((1<<CLOCK)|(1<<LATCH));    // CLOCK en LATCH is OUTPUT

    pinSet(LATCH, HIGH);
    unsigned char tmp;
    tmp = buttons();
    if (tmp == 0) { return -1;
    }
    printf("%X",tmp);
    return 0;
}

unsigned char buttons()
{
    int i=0;
    pinSet(LATCH, LOW);
    pinSet(CLOCK, LOW);
    unsigned char btns = 0;
    unsigned char InBit1;
    for (i = 0; i < BITS; i++) {
        InBit1 = (INA & (1<<DATA1));
        //InBit2 = (INA & (1<<DATA2));
        btns = (btns<<1) | InBit1;
    }
    return btns;
}

void pinInput(int pin)
{
    uint32_t mask = 1 << pin;
    DIRA &= ~mask;
}

void pinOutput(int pin)
{
    uint32_t mask = 1 << pin;
    DIRA |= mask;
}

void pinSet(int pin, int value)
{
    uint32_t mask = 1 << pin;
    uint32_t data = (value & 1) << pin;
    OUTA = (OUTA & ~mask) | data;
}
