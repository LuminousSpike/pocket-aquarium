// main.c
#include <gb/cgb.h>
#include <gb/gb.h>
#include <rand.h>
#include <stdio.h>

#include "../res/background.h"
#include "../res/coin_sprite.h"
#include "../res/cursor_sprite.h"
#include "../res/food_sprite.h"
#include "../res/guppy_sprite.h"
#include "../res/hungry_guppy_sprite.h"
#include "coin.h"
#include "cursor.h"
#include "fish.h"
#include "food.h"
#include "score.h"

#define MAX_SPRITES 40
uint8_t
    allocated_sprites[MAX_SPRITES]; // Tracks whether each sprite ID is in use

void
init_colors(void)
{
    // Set background palette for Game Boy Color
    set_bkg_palette(0, background_PALETTE_COUNT, background_palettes);

    // Set sprite palette
    set_sprite_palette(0, cursor_sprite_PALETTE_COUNT, cursor_sprite_palettes);
    set_sprite_palette(1, guppy_sprite_PALETTE_COUNT, guppy_sprite_palettes);
    set_sprite_palette(2, hungry_guppy_sprite_PALETTE_COUNT,
                       hungry_guppy_sprite_palettes);
    set_sprite_palette(3, coin_sprite_PALETTE_COUNT, coin_sprite_palettes);
    set_sprite_palette(4, food_sprite_PALETTE_COUNT, food_sprite_palettes);
}

void
init_background(void)
{
    // Load the background tiles into VRAM (tile data for the background)
    set_bkg_data(background_TILE_ORIGIN, background_TILE_COUNT,
                 background_tiles);

    // Set up the background map (layout of tiles on the screen)
    set_bkg_tiles(0, 0, background_WIDTH / 8, background_HEIGHT / 8,
                  background_map);

    // Optionally: Set background attributes (for Game Boy Color, different
    // palettes per tile) If you're using background attributes, set them like
    // this:
    if (background_MAP_ATTRIBUTES)
    {
        VBK_REG = 1; // Switch to VRAM bank 1 to modify attributes
        set_bkg_tiles(0, 0, background_WIDTH / 8, background_HEIGHT / 8,
                      background_map_attributes);
        VBK_REG = 0; // Switch back to VRAM bank 0 to modify tile numbers
    }
}

void
init(void)
{
    init_colors();

    // Initialize the screen
    DISPLAY_OFF;

    // Load background tiles
    init_background();

    // Initialize game objects
    init_cursor();
    init_fish();
    init_food();
    init_coins();

    // Turn the display back on and show background and sprites
    DISPLAY_ON;
    SPRITES_8x16;
    SHOW_BKG;
    SHOW_SPRITES;
}

void
main(void)
{
    score_t score;
    init();

    score_init(&score);

    // Main game loop
    while (1)
    {
        // Handle input and update game state
        move_cursor();
        drop_food(&score);
        update_fish();
        update_food();
        update_coins(&score);

        score_render(&score);

        // Wait for VBLANK to avoid tearing
        wait_vbl_done();
    }
}

// Initialize the sprite allocation system (this should be called once, at the
// start)
void
init_sprite_allocator(void)
{
    for (uint8_t i = 0; i < MAX_SPRITES; i++)
    {
        allocated_sprites[i] = 0; // Mark all sprite IDs as free
    }
}

// Allocates a sprite and returns the sprite ID, or NO_SPRITE if no sprites are
// available
uint8_t
allocate_sprite(void)
{
    for (uint8_t i = 0; i < MAX_SPRITES; i++)
    {
        if (allocated_sprites[i] == 0)
        {
            allocated_sprites[i] = 1; // Mark sprite as allocated
            return i;                 // Return the allocated sprite ID
        }
    }
    return NO_SPRITE; // No available sprite, return NO_SPRITE
}

// Frees a sprite, making its ID available again
void
free_sprite(uint8_t sprite_id)
{
    if (sprite_id < MAX_SPRITES)
    {
        allocated_sprites[sprite_id] = 0; // Mark sprite as free
        hide_sprite(sprite_id);           // Hide the sprite
    }
}

void
play_sound(uint8_t sound_id)
{
    // TODO: Implement actual sound playing
    (void)sound_id; // Suppress unused parameter warning
}
