//libraries n stuff
#include <ti/getcsc.h>
#include <sys/util.h>
#include <compression.h>
#include <graphx.h>
#include <keypadc.h>
#include <time.h>
#include <math.h>
#include "gfx/wolfsp.h"
#include "loadSprites.h"
#include "functions.h"

//frame limit
#define TARGET_FRAMERATE 30
#define TARGET_FRAME_TIME (CLOCKS_PER_SEC / TARGET_FRAMERATE)

//main stuffz
int main(void) {
	
	if (wolfsp_init() == 0) {return 1;}
	initGfx(); //setup / initialization
	decompressSprites(); //decompressing spritezzz
	
	//main loop
	do {
		clock_t frame_start = clock(); //starts frame timer
		
		timerStuff(); //does animation related math
		getInput(); //calls getInput function to, well, get input, and do stuff with said input
		if (!paused) {rayMath();} //does ray related calculations if unpaused
		renderWindow(); //graphics rendering and raycast math
		
		//delays next frame
		clock_t frame_time = clock() - frame_start;
		do {frame_time = clock() - frame_start;} while (frame_time < TARGET_FRAME_TIME);
	} while(inGame == true);
	
	//ends gfx process and frees memory of pesky lil sprites
    gfx_End();
	free(strip1);
	free(lowerScreenHUD1);
	free(lowerScreenHUD2);
    return 0;
}