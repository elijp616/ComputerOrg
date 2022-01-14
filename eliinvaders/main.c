#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "text.h"
#include "gba.h"
#include "space.h"
#include "losebg.h"

void initialize(void);

void goToStart(void);
void start(void);
void goToGame(void);
void game(void);
void goToPause(void);
void pause(void);
void goToWin(void);
void win(void);
void goToLose(void);
void lose(void);

enum {START, GAME, PAUSE, WIN, LOSE};
int state;

int seed;

unsigned short buttons;
unsigned short oldButtons;

char buffer[41];

int main(void) {
    initialize();
    while(1) {
        oldButtons = buttons;
        buttons = BUTTONS;

        switch(state) {
            case START:
                start();
                break;
            case GAME:
                game();
                break;
            case PAUSE:
                pause();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
        }
    }
}

void initialize(void) {

    REG_DISPCTL = MODE3 | BG2_ENABLE | DISP_BACKBUFFER;

    goToStart();
}

void goToStart(void) {

    DMANow(3, &spacePal, PALETTE,  256);
    drawFullscreenImage3(spaceBitmap);
    waitForVBlank();
    state = START;

}

void start(void) {
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {

        goToGame();
        initGame();
    }
}

void goToGame(void) {
    state = GAME;
}

void game(void) {

    updateGame();
    drawGame();

    sprintf(buffer, "Aliens Remaining: %d", aliensRemaining);
    drawString3(5, 145, buffer, WHITEID);

    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_SELECT))
        goToStart();
    if (BUTTON_PRESSED(BUTTON_START))
        goToPause();
    else if (aliensRemaining == 0)
        goToWin();
    else if (reachedBar)
        goToLose();
}

void goToPause(void) {

    fillScreen3(GRAYID);
    drawString3(120-15, 80-3, "Pause", BLACKID);

    waitForVBlank();
    state = PAUSE;
}

void pause(void) {

    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START))
        goToGame();
    else if (BUTTON_PRESSED(BUTTON_SELECT))
        goToStart();
}

void goToWin(void) {

    fillScreen3(GREENID);
    drawString3(120-9, 80-3, "Win", BLACKID);

    waitForVBlank();


    state = WIN;
}

void win(void) {

    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_SELECT))
        goToStart();
}

void goToLose(void) {

    DMANow(3, &losebgPal, PALETTE,  256);
    drawFullscreenImage3(losebgBitmap);

    waitForVBlank();

    state = LOSE;
}

void lose(void) {


    waitForVBlank();
    

    if (BUTTON_PRESSED(BUTTON_SELECT))
        goToStart();
}