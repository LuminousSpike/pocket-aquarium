//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(cursor_sprite)

const palette_color_t cursor_sprite_palettes[4] = {
	RGB8(  0,  0,  0), RGB8( 55,148,110), RGB8(  0,  0,  0), RGB8(  0,  0,  0)
	
};

const uint8_t cursor_sprite_tiles[32] = {
	0x00,0x3c,0x18,0x66,
	0x3c,0xc3,0x7e,0x81,
	0x7e,0x81,0x7e,0x81,
	0x18,0xe7,0x18,0x24,
	0x18,0x24,0x18,0x24,
	0x18,0x24,0x18,0x24,
	0x18,0x24,0x18,0x24,
	0x18,0x24,0x00,0x3c
	
};

const metasprite_t cursor_sprite_metasprite0[] = {
	METASPR_ITEM(-8, -4, 0, S_PAL(0)),
	METASPR_TERM
};

const metasprite_t* const cursor_sprite_metasprites[1] = {
	cursor_sprite_metasprite0
};
