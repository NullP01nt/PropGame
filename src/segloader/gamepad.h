#ifndef __GBL_GAMEPAD_H
#define __GBL_GAMEPAD_H

// Button values
#define BUTTON_RIGHT   (1<<7)
#define BUTTON_LEFT    (1<<6)
#define BUTTON_DOWN    (1<<5)
#define BUTTON_UP      (1<<4)
#define BUTTON_START   (1<<3)
#define BUTTON_SELECT  (1<<2)
#define BUTTON_B       (1<<1)
#define BUTTON_A       (1<<0)

#define PAD_BIT_LENGTH	8

void InitGPadIO(void);
void readPads(void);
uint8_t readButtons(int);

#endif
