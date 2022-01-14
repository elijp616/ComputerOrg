#ifndef GBA_H
#define GBA_H

// Player Struct
//
typedef struct {
	int row;
	int col;
	int cdel;
	int height;
	int width;
	unsigned char color;
	int bulletTimer;
} PLAYER;

// Bullet Struct
typedef struct {
	int row;
	int col;
	int rdel;
	int cdel;
	int height;
	int width;
	unsigned char color;
	int active;
} BULLET;

// Alien Struct
typedef struct {
	int row;
	int col;
	int rdel;
	int cdel;
	int height;
	int width;
	int spec;
	int active;
} ALIEN;

#define BULLETCOUNT 5
#define ALIENCOUNT 32

extern PLAYER player;
extern BULLET bullets[BULLETCOUNT];
extern ALIEN aliens[ALIENCOUNT];
extern int aliensRemaining;
extern int time;
extern int reachedBar;

#define NUMCOLORS 6
enum {BLACKID=(256-NUMCOLORS), BLUEID, GREENID, REDID, WHITEID, GRAYID};
extern unsigned short colors[NUMCOLORS];

void initGame(void);
void updateGame(void);
void drawGame(void);
void drawBar(void);
void initPlayer(void);
void updatePlayer(void);
void drawPlayer(void);
void initBullets(void);
void fireBullet(void);
void updateBullet(BULLET *);
void drawBullet(BULLET *);
void initAliens(void);
void updateAlien(ALIEN *);
void drawAlien(ALIEN *);
#endif