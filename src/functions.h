#include <graphx.h>
#include <math.h>
#include <stdbool.h>
#include "gfx/wolfsp.h"
#include "loadSprites.h"
#ifndef GET_INPUT_H
#define GET_INPUT_H

extern float playerX;
extern float playerY;
extern int playerAngle;
extern int movementSpeed;
extern int turnSpeed;
extern int fov;
extern int totalRays;
extern int columnHeight;
extern int frames;
extern int pressing;
extern int justTurned;
extern int degreesBetweenRays;
extern int totalRecursions;
extern int hitText;
extern int grayShades[12];

extern int hit;
extern int rayAngle;
extern int rayX;
extern int rayY;
extern int newRayX;
extern int newRayY;
extern float rayIntersectX;
extern float rayIntersectY;
extern float distanceToIntersect;
extern int i;
extern int j;
extern int k;
extern int kLimit;
extern int chosenColor;

extern int ceilingColor;
extern int floorColor;
extern int walls[4][4];

extern int inGame;
extern int paused;


void getInput(void);
void renderWindow(void);
void initGfx(void);
void timerStuff(void);
void rayMath(void);
bool cclockwise(float a, float b, float c, float d, float e, float f);
bool lineintersect(float a, float b, float c, float d, float e, float f, float g, float h);


#endif