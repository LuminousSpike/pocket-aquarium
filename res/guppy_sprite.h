//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_guppy_sprite_H
#define METASPRITE_guppy_sprite_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define guppy_sprite_TILE_ORIGIN 0
#define guppy_sprite_TILE_W 8
#define guppy_sprite_TILE_H 16
#define guppy_sprite_WIDTH 8
#define guppy_sprite_HEIGHT 16
#define guppy_sprite_TILE_COUNT 2
#define guppy_sprite_PALETTE_COUNT 1
#define guppy_sprite_COLORS_PER_PALETTE 4
#define guppy_sprite_TOTAL_COLORS 4
#define guppy_sprite_PIVOT_X 4
#define guppy_sprite_PIVOT_Y 8
#define guppy_sprite_PIVOT_W 8
#define guppy_sprite_PIVOT_H 16
extern const metasprite_t* const guppy_sprite_metasprites[1];

BANKREF_EXTERN(guppy_sprite)

extern const palette_color_t guppy_sprite_palettes[4];
extern const uint8_t guppy_sprite_tiles[32];

#endif
