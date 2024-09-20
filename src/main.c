// main.c
#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include <rand.h>
#include "../res/background.h"
#include "fish.h"
#include "coin.h"
#include "cursor.h"
#include "food.h"
#include "../res/blank_tile.h"

#define MAX_SPRITES 40
uint8_t allocated_sprites[MAX_SPRITES];  // Tracks whether each sprite ID is in use

// Define background palette (3 colors + transparent)
const UWORD bkg_palette[] = {
    RGB(31, 31, 31),  // Light cyan
    RGB(12, 24, 31),  // Dark blue
    RGB(31, 16, 8),   // Sandy brown
    RGB(8, 24, 8)     // Green
};

// Define sprite palette (3 colors + transparent)
const UWORD sprite_palette[] = {
    RGB_RED, RGB_GREEN, RGB_BLUE, RGB_BLACK
};

void init_colors(void) {
    // Set background palette
    set_bkg_palette(0, 1, bkg_palette);
    
    // Set sprite palette
    set_sprite_palette(0, 1, sprite_palette);
}

void init_background(void) {
    // Load the background tiles into VRAM
    set_bkg_data(0, background_TILE_COUNT, background_tiles);

    // Set up the background map
    set_bkg_tiles(0, 0, 20, 18, background_map);
}

void init(void) {
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

void main(void) {
    init();

    // Main game loop
    while(1) {
        // Handle input and update game state
        move_cursor();
        drop_food();
        update_fish();
        update_food();
        update_coins();

        // Wait for VBLANK to avoid tearing
        wait_vbl_done();
    }
}

// Initialize the sprite allocation system (this should be called once, at the start)
void init_sprite_allocator(void) {
    for (uint8_t i = 0; i < MAX_SPRITES; i++) {
        allocated_sprites[i] = 0;  // Mark all sprite IDs as free
    }
}

// Allocates a sprite and returns the sprite ID, or NO_SPRITE if no sprites are available
uint8_t allocate_sprite(void) {
    for (uint8_t i = 0; i < MAX_SPRITES; i++) {
        if (allocated_sprites[i] == 0) {
            allocated_sprites[i] = 1;  // Mark sprite as allocated
            return i;  // Return the allocated sprite ID
        }
    }
    return NO_SPRITE;  // No available sprite, return NO_SPRITE
}

// Frees a sprite, making its ID available again
void free_sprite(uint8_t sprite_id) {
    if (sprite_id < MAX_SPRITES) {
        allocated_sprites[sprite_id] = 0;  // Mark sprite as free
        hide_sprite(sprite_id);  // Hide the sprite
    }
}

void play_sound(uint8_t sound_id) {
    // TODO: Implement actual sound playing
    (void)sound_id; // Suppress unused parameter warning
}