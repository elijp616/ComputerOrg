#include "myLib.h"
#include "gba.h"
#include "alien.h"
#include "alien1.h"

PLAYER player;
BULLET bullets[BULLETCOUNT];
ALIEN aliens[ALIENCOUNT];
int aliensRemaining;
int reachedBar;
int time;
void initGame(void) {

	initPlayer();
    initBullets();
    initAliens();

	reachedBar = 0;

	aliensRemaining = ALIENCOUNT;

    unsigned short colors[NUMCOLORS] = {BLACK, BLUE, GREEN, RED, WHITE, GRAY};


    for (int i = 0; i < NUMCOLORS; i++) {
        PALETTE[256-NUMCOLORS+i] = colors[i];
    }
	PALETTE[1] = 0x0BFE;
}

void updateGame(void) {

	updatePlayer();

	for (int i = 0; i < BULLETCOUNT; i++)
		updateBullet(&bullets[i]);

	for (int i = 0; i < ALIENCOUNT; i++)
		updateAlien(&aliens[i]);
	time++;
}

void drawGame(void) {

    fillScreen3(BLACKID);

	drawPlayer();

	for (int i = 0; i < BULLETCOUNT; i++)
		drawBullet(&bullets[i]);

	for (int i = 0; i < ALIENCOUNT; i++)
		drawAlien(&aliens[i]);
}

void initPlayer(void) {
	player.row = 130;
	player.col = 118;
	player.cdel = 2;
	player.height = 10;
	player.width = 5;
	player.color = REDID;
	player.bulletTimer = 20;
}

void updatePlayer(void) {

	if (BUTTON_HELD(BUTTON_LEFT)
		&& player.col >= player.cdel) {

		player.col -= player.cdel;

	} else if (BUTTON_HELD(BUTTON_RIGHT)
		&& player.col + player.width - 1 < SCREENWIDTH - player.cdel) {

		player.col += player.cdel;
	}

	if (BUTTON_PRESSED(BUTTON_A) && player.bulletTimer >= 17) {

		fireBullet();
		player.bulletTimer = 0;
	}

	player.bulletTimer++;
}

void drawPlayer(void) {
	drawRect3(player.col, player.row, player.width, player.height, player.color);
	drawRect3(player.col - player.width, player.row + (player.height/2), player.width * 3,
		player.height/2, player.color);
}

void initBullets(void) {
	for (int i = 0; i < BULLETCOUNT; i++) {
		bullets[i].height = 4;
		bullets[i].width = 2;
		bullets[i].row = bullets[i].height;
		bullets[i].col = 0;
		bullets[i].rdel = -2;
        bullets[i].cdel = 0;
		bullets[i].color = WHITEID;
		bullets[i].active = 0;
	}
}

void fireBullet(void) {

	for (int i = 0; i < BULLETCOUNT; i++) {
		if (!bullets[i].active) {

			bullets[i].row = player.row;
			bullets[i].col = player.col + player.width/2
				- bullets[i].width/2;

			bullets[i].active = 1;

			break;
		}
	}
}

void updateBullet(BULLET* b) {

	if (b->active) {
		if (b->row + b->height-1 >= 0
            && b->col + b->cdel > 0
            && b->col + b->cdel < SCREENWIDTH-1) {

			b->row += b->rdel;
            b->col += b->cdel;
		} else {
			b->active = 0;
		}
	}
}

void drawBullet(BULLET* b) {
	if(b->active) {
		drawRect3(b->col, b->row, b->width, b->height, b->color);
	}
}

void initAliens(void) {

	for (int i = 0; i < ALIENCOUNT; i++) {
		aliens[i].row = 18 * ((i / 8) + 1);
		aliens[i].col = 58 + (16 * (i % 8) + 1);
        aliens[i].spec = i & 1;
		aliens[i].active = 1;
		aliens[i].height = 9;
		aliens[i].width = 12;
		}
}


void updateAlien(ALIEN* b) {

	if (b->active) {
		if ((time % 100 == 0) && (time % 200 != 0))
			b->col += 8;
		if (time % 200 == 0)
			b->col -= 8;
		
		if (time % 437 == 0)
			b->row += 9;

		if (b->row >= 120)
			reachedBar = 1;

		for (int i = 0; i < BULLETCOUNT; i++) {
			if (bullets[i].active && collision(b->col, b->row, b->width, b->height,
				bullets[i].col, bullets[i].row, bullets[i].width, bullets[i].height)) {

				bullets[i].active = 0;
				b->active = 0;

				aliensRemaining--;
			}
		}
	}
}

void drawAlien(ALIEN* a) {
	if(a->active) {
		if (a->spec) {
			
			drawImage3(a->col, a->row, a->width, a->height, alien1Bitmap);
		} else {
			drawImage3(a->col, a->row, a->width, a->height, alienBitmap);
		}
	}
}