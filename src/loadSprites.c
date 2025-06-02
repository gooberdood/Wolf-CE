#include <compression.h>
#include <graphx.h>
#include "gfx/wolfsp.h"

gfx_sprite_t *strip1;
gfx_sprite_t *lowerScreenHUD1;
gfx_sprite_t *lowerScreenHUD2;
gfx_sprite_t *pistol1;

//decompresses sprites
void decompressSprites(void) {
	strip1 = gfx_MallocSprite(strip1_width, strip1_height);
	zx0_Decompress(strip1, strip1_compressed);
	lowerScreenHUD1 = gfx_MallocSprite(lowerScreenHUD1_width, lowerScreenHUD1_height);
	zx0_Decompress(lowerScreenHUD1, lowerScreenHUD1_compressed);
	lowerScreenHUD2 = gfx_MallocSprite(lowerScreenHUD2_width, lowerScreenHUD2_height);
	zx0_Decompress(lowerScreenHUD2, lowerScreenHUD2_compressed);
	pistol1 = gfx_MallocSprite(pistol1_width, pistol1_height);
	zx0_Decompress(pistol1, pistol1_compressed);
}