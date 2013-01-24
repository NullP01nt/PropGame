/**
 * @file rock_paper_scissors.c
 * This is the main rock_paper_scissors program start point.
 */

/**
 * Main program function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cog.h>
#include <ctype.h>
#include <propeller.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sd.h>
#include <time.h>

#include "pins.h"
#include "vga_text.h"
#include "gamepad.h"

#define BLANK           0x20
#define CLR_ROW(x) vgaText_setXY(0,x);vgaText_print("                              ");

#define CURSOR_COL      0
#define CURSOR_CHAR     0xBB

#define OPT_COL         2
#define OPT_ROW_START   2
#define OPT_ROW_MAX     4

#define PLAYER_COL      2
#define COMP_COL        14

#define COL_0_X 0
#define COL_1_X 14
#define ROW_MIN 2
#define ROW_MAX    12
uint8_t PAD_ONE;

const char *options[3] = { "Rock    " , "Paper   " , "Scissors" };   //maybe Lizard, spock etc :P
char *result[3] = { "Tied  " , "Winner" , "Lost  " };

int csr_col = 0, old_col = 0;
int csr_row = 2, old_row = 2;
int inGame = 1;

void drawTitle(void) {
    vgaText_setXY(4,0);
    vgaText_print("Rock, Paper, Scissors");
}

void drawOptions(void) {
    int txt_col=OPT_COL, txt_row=OPT_ROW_START;
    int prntNrOptions;
    for(prntNrOptions=0; prntNrOptions<3; prntNrOptions++) {
        vgaText_setXY(txt_col,txt_row);
        vgaText_print((char *)options[prntNrOptions]);
        txt_row++;
    }
}

void csr_redraw(void) {
    vgaText_setXY(old_col * COL_1_X, old_row);
    vgaText_out(BLANK);

    if (csr_row > OPT_ROW_MAX) {
        csr_row = OPT_ROW_MAX;
    } else if (csr_row < OPT_ROW_START) {
        csr_row = OPT_ROW_START;
    }
    vgaText_setXY(CURSOR_COL, csr_row);
    vgaText_out(CURSOR_CHAR);
}

void clr_battle(void) {
    int i;
    for(i=6;i<=12;i++) {
        CLR_ROW(i);
    }
}

int leBigBoss(void) {
    srand(time(NULL));
    int randomChoice;
    //randomChoice = 0 + rand()%3;
    randomChoice = rand()%3;
    return randomChoice;
}

void leBattle(int choice_gamer){
    inGame = 0;
    int boss;
    boss = leBigBoss();
    vgaText_setXY(COMP_COL,6);
    vgaText_print("PC:");
    vgaText_setXY(COMP_COL,7);
    vgaText_print((char *)options[boss]);
    vgaText_setXY(2,9);
    vgaText_print(result[(boss-choice_gamer+3)%3]);
}

void waitRetry(void) {
    vgaText_setXY(2,12);
    vgaText_print("PRESS START TO RETRY");
    while(1) {
        readPads();
        if(PAD_ONE & BUTTON_START) {
            vgaText_setXY(2,12);
            vgaText_str("START PRESSED");
            clr_battle();
            inGame = 1;
            break;
        }
    }
    waitcnt(CLKFREQ/6+CNT);
}

void game(void) {
//    vgaText_setXY(1,13);
//    vgaText_str("                     ");
    int choice_gamer;
    
    while(inGame) {
        readPads();
        csr_redraw();
        if (PAD_ONE == 0xFF) {
            vgaText_setXY(PLAYER_COL,6);
            vgaText_print("Gamepad 1 disconnected!");
        } else if(PAD_ONE == 0x00) {
            CLR_ROW(6);
        } else if (PAD_ONE & BUTTON_A) {
            vgaText_setXY(PLAYER_COL,6);
            vgaText_print("Keuze:");
            vgaText_setXY(PLAYER_COL,7);
            choice_gamer=(csr_row-2);
            vgaText_print((char *)options[choice_gamer]);
            leBattle(choice_gamer);
        } else if (PAD_ONE & BUTTON_UP) {
            old_row = csr_row;
            csr_row--;
            csr_redraw();
        } else if (PAD_ONE & BUTTON_DOWN) {
            old_row = csr_row;
            csr_row++;
            csr_redraw();
        }
        waitcnt(CLKFREQ/6+CNT);
    }
}

int main(void)
{
    InitGPadIO();
    waitcnt(CLKFREQ/1+CNT);
    vgaText_start(VGA_BASE_PIN);
  
    drawTitle();
    drawOptions();

    while (1) {
        game();
        waitRetry();
    }
    return 0;
}