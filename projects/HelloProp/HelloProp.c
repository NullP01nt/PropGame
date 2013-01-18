/**
 * @file HelloProp.c
 * This is the main HelloProp program start point.
 */

/**
 * Main program function.
 */
#include <stdio.h>
#include <propeller.h>

int main(void)
{
    char* text = "World";
    int n = 0;
    while(1) {
        waitcnt(CLKFREQ/10+CNT);
        printf("Hello, %s! [%d]\n",text,n);
        n++;
    }
    return 0;
}
