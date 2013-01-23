/**
 * @file rock_paper_scissors.c
 * This is the main rock_paper_scissors program start point.
 */

/**
 * Main program function.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int choice_gamer, choice_pc;
    const char *options[] = { "Rock" , "Paper" , "Scissors" };   //maybe Lizard, spock etc :P
    const char *result[] = { "Tied" , "Winner" , "Losed" };

    while (1) {
        //game
        printf("%c,%c,%c",options[0],options[1],options[2]);
    }

    return 0;
}

