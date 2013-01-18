/**
 * @file NES_Test.c
 * This is the main NES_Test program start point.
 */

/**
 * Main program function.
 */

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
#define BTN_B       (1<<1)
#define BTN_A       (1<<0)

void pinSet(int,int);
unsigned char buttons(void);
void readButtons(void);
int init_gamepad(void);

unsigned char P1_BUTTONS;
unsigned char P2_BUTTONS;

void print_buttons(unsigned char);

int main()
{
    printf("Hello world!\n");
    init_gamepad();
    while(1) {
        readButtons();
        print_buttons(P1_BUTTONS);
        print_buttons(P2_BUTTONS);
/*        if(P1_BUTTONS & BTN_START) {
            printf("[P1] Start pressed!\n");
        } else if(P1_BUTTONS & BTN_SELECT) {
            printf("[P1] Select pressed!\n");
        } else if(P1_BUTTONS & BTN_A) {
            printf("[P1] A pressed!\n");
        } else if(P1_BUTTONS & BTN_B) {
            printf("[P1] B pressed!\n");
        } else if(P1_BUTTONS & BTN_UP) {
            printf("[P1] Up pressed!\n");
        } else if(P1_BUTTONS & BTN_DOWN) {
            printf("[P1] Down pressed!\n");
        } else if(P1_BUTTONS & BTN_LEFT) {
            printf("[P1] Left pressed!\n");
        } else if(P1_BUTTONS & BTN_RIGHT) {
            printf("[P1] Right pressed!\n");
        }

        if(P2_BUTTONS & BTN_START) {
            printf("[P2] Start pressed!\n");
        } else if(P2_BUTTONS & BTN_SELECT) {
            printf("[P2] Select pressed!\n");
        } else if(P2_BUTTONS & BTN_A) {
            printf("[P2] A pressed!\n");
        } else if(P2_BUTTONS & BTN_B) {
            printf("[P2] B pressed!\n");
        } else if(P2_BUTTONS & BTN_UP) {
            printf("[P2] Up pressed!\n");
        } else if(P2_BUTTONS & BTN_DOWN) {
            printf("[P2] Down pressed!\n");
        } else if(P2_BUTTONS & BTN_LEFT) {
            printf("[P2] Left pressed!\n");
        } else if(P2_BUTTONS & BTN_RIGHT) {
            printf("[P2] Right pressed!\n");
        }*/
//        printf("0x%X\n",P1_BUTTONS);
        waitcnt(CLKFREQ/2+CNT);
    }
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

void print_buttons(unsigned char input) {
    int i=BITS;
    printf("RLDUSSBA\n");
    for(i=BITS;i>0;i--) {
        printf("%d",input&(1<<(i-1))?1:0);
    }
    printf("\n");
}

void readButtons() {
    int i=0;
    pinSet(LATCH,LOW);
    pinSet(CLOCK,LOW);
    uint8_t p1b=0,p2b=0;
    uint8_t i1=0,i2=0;
    for(i=BITS;i>0;i--) {
        i1 = (INA & (1<<DATA1)) ? 0 : 1;
        i2 = (INA & (1<<DATA2)) ? 0 : 1;
        p1b |= (i1<<(BITS-i));
        p2b |= (i2<<(BITS-i));
        pinSet(CLOCK,HIGH);
        waitcnt(500+CNT);
        pinSet(CLOCK,LOW);
    }
    P1_BUTTONS = p1b;
    P2_BUTTONS = p2b;
}

unsigned char buttons()
{
    int i=0;
    pinSet(LATCH, LOW);
    pinSet(CLOCK, LOW);
    unsigned char btns = 0;
    unsigned char InBit1 = 0;
    for (i = BITS; i > 0; i--) {
        InBit1 = (INA & (1<<DATA1)) ? 0 : 1;
        btns |= (InBit1<<(BITS-i));
        pinSet(CLOCK,HIGH);
        waitcnt(500+CNT);
        pinSet(CLOCK,LOW);
    }
    pinSet(LATCH,HIGH);
    return btns;
}

void pinSet(int pin, int value)
{
    uint32_t mask = 1 << pin;
    uint32_t data = (value & 1) << pin;
    OUTA = (OUTA & ~mask) | data;
}
