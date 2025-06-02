#include <keypadc.h>
#include <compression.h>
#include <graphx.h>
#include <math.h>
#include "gfx/wolfsp.h"
#include "functions.h"
#include "loadSprites.h"

float playerX = 0;
float playerY = 0;
int playerAngle = 360;
int movementSpeed = 1;
int turnSpeed = 3;
int frames = 0;
int pressing = false;
int justTurned = false;
int renderDistance = 100;
int rayStepDistance = 100;
int columnHeight;
int totalRays = 15;
int fov = 30;
int totalRecursions = 0;
int grayShades[12] = {2,3,4,5,6,7,8,9,10,11,12,13};

int hit;
int rayAngle;
int rayX;
int rayY;
int newRayX;
int newRayY;
float rayIntersectX;
float rayIntersectY;
float distanceToIntersect;
int degreesBetweenRays;
int i;
int j;
int k;
int kLimit;
int chosenColor;

int floorColor = 15;
int ceilingColor = 14;
int walls[4][4] = {{-20,20,20,20}, {20,20,20,-20}, {20,-20,-20,-20}, {-20,-20,-20,20}};

int inGame = true;
int paused = false;


bool cclockwise(float a, float b, float c, float d, float e, float f) {
	return ((f-b)*(c-a)) > ((d-b)*(e-a));
}

bool lineintersect(float a, float b, float c, float d, float e, float f, float g, float h) {
	bool w = cclockwise(a,b,e,f,g,h);
	bool x = cclockwise(c,d,e,f,g,h);
	bool y = cclockwise(a,b,c,d,e,f);
	bool z = cclockwise(a,b,c,d,g,h);
	return ((w != x) && (y != z));
}


//initialize gfx / set up
void initGfx(void) {
    gfx_Begin();
	gfx_SetDrawBuffer();
	//sets palette and transparent color
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
	gfx_SetTransparentColor(0);
	gfx_SetTextTransparentColor(0);
	gfx_SetTextBGColor(0);
	gfx_SetTextFGColor(1);
	gfx_SetTextConfig(gfx_text_clip);
}


void getInput(void) {
	//scans the keypad, then checks inputs
	kb_Scan();
	if (kb_Data[6] & kb_Clear) {
		if (!pressing) {
			if (!paused) {paused = true;} else {inGame = false;}
		}
		pressing = true;
	} else {pressing = false;}
	
	if (kb_Data[7] & kb_Left) {playerAngle -= turnSpeed; justTurned = true;}
	if (kb_Data[7] & kb_Right) {playerAngle += turnSpeed; justTurned = true;}
	if (justTurned) {
		if (playerAngle < 1) {playerAngle += 360;}
		if (playerAngle > 360) {playerAngle -= 360;}
		justTurned = false;
	}
	
	if (kb_Data[7] & kb_Up) {
		playerX += movementSpeed * cosf((90-playerAngle)*M_PI/180);
		playerY += movementSpeed * sinf((90-playerAngle)*M_PI/180);
	}
	if (kb_Data[7] & kb_Down) {
		playerX -= movementSpeed * cosf((90-playerAngle)*M_PI/180);
		playerY -= movementSpeed * sinf((90-playerAngle)*M_PI/180);
	}
}


//raycast related math (sigma stuff)
void rayMath(void) {
    degreesBetweenRays = fov/totalRays;
	totalRecursions = 0;
	for (i = 0; i < totalRays; i++) {
		hit = false;
		rayAngle = i * degreesBetweenRays + playerAngle - (fov/2);
		if (rayAngle < 1) {rayAngle += 360;}
		if (rayAngle > 360) {rayAngle -= 360;}
		rayX = playerX;
		rayY = playerY;
		newRayX = 0;
		newRayY = 0;
		
		for (j = 0; j < (renderDistance / rayStepDistance); j++) {
			newRayX = rayX + (rayStepDistance * round(sinf((90-rayAngle)*M_PI/180)));
			newRayY = rayY + (rayStepDistance * round(cosf((90-rayAngle)*M_PI/180)));
			
			kLimit = sizeof(walls);
			for (k = 0; k < kLimit; k++) {
				int wallX1 = walls[k][0];
				int wallY1 = walls[k][1];
				int wallX2 = walls[k][2];
				int wallY2 = walls[k][3];
				if (lineintersect(newRayX, newRayY, rayX, rayY, walls[k][0], walls[k][1], walls[k][2], walls[k][3])) {
					
					rayIntersectX = (((newRayX*rayY - newRayY*rayX)*(wallX1 - wallX2)) - ((newRayX-rayX)*(wallX1*wallY2 - wallY1*wallX2)));
					rayIntersectX = rayIntersectX / (((newRayX - rayX)*(wallY1 - wallY2)) - ((newRayY - rayY)*(wallX1 - wallX2)));
					rayIntersectY = (((newRayX*rayY - newRayY*rayX)*(wallY1 - wallY2)) - ((newRayX-rayX)*(wallX1*wallY2 - wallY1*wallX2)));
					rayIntersectY = rayIntersectY / (((newRayX - rayX)*(wallY1 - wallY2)) - ((newRayY - rayY)*(wallX1 - wallX2)));
					
					distanceToIntersect = sqrt(pow(rayIntersectX-playerX, 2) + pow(rayIntersectY-playerY, 2));
					columnHeight = 240 / (distanceToIntersect/5);
					
					if (distanceToIntersect >= 120) {chosenColor = grayShades[0];}
					else if (distanceToIntersect > 110) {chosenColor = grayShades[1];}
					else if (distanceToIntersect > 100) {chosenColor = grayShades[2];}
					else if (distanceToIntersect > 90) {chosenColor = grayShades[3];}
					else if (distanceToIntersect > 80) {chosenColor = grayShades[4];}
					else if (distanceToIntersect > 70) {chosenColor = grayShades[5];}
					else if (distanceToIntersect > 60) {chosenColor = grayShades[6];}
					else if (distanceToIntersect > 50) {chosenColor = grayShades[7];}
					else if (distanceToIntersect > 40) {chosenColor = grayShades[8];}
					else if (distanceToIntersect > 30) {chosenColor = grayShades[9];}
					else if (distanceToIntersect > 20) {chosenColor = grayShades[10];}
					else if (distanceToIntersect > 10) {chosenColor = grayShades[11];}
					else {chosenColor = grayShades[11];}
					
					gfx_SetColor(chosenColor);
					gfx_FillRectangle(round(i*(320/totalRays)), round((240-columnHeight)/2), round(320/totalRays), columnHeight);
					
					hit = true;
				}
				totalRecursions++;
			}
			if (hit) {j = round(renderDistance * rayStepDistance);}
			
			rayX = newRayX;
			rayY = newRayY;
		}
	}
}


//renders graphics to screen
void renderWindow(void) {
	//background
	gfx_FillScreen(0);
	gfx_SetColor(14);
	gfx_FillRectangle(0, 0, 320, 100);
	gfx_SetColor(15);
	gfx_FillRectangle(0, 140, 320, 100);
	
	rayMath();
	
	gfx_Sprite_NoClip(lowerScreenHUD1, 0, 200);
	gfx_Sprite_NoClip(lowerScreenHUD2, 160, 200);
	
	gfx_SetTextXY(1,1);
	gfx_PrintInt(playerAngle, 1);
	gfx_SetTextXY(1,10);
	gfx_PrintInt(round(playerX), 1);
	gfx_PrintString(", ");
	gfx_PrintInt(round(playerY), 1);
	gfx_SetTextXY(1,19);
	gfx_PrintInt(totalRecursions, 1);
	
	gfx_SwapDraw();
}


//timer related stuff, per frame stuff
void timerStuff(void) {
	frames += 1;
	if (frames >= 30) {
		frames = 0;
	}
}