#include "fish.h"
#include "../res/guppy_sprite.h"
#include "../res/hungry_guppy_sprite.h"
#include "../res/blank_tile.h"
#include <rand.h>
#include "coin.h"
#include "food.h"

Fish fish_list[MAX_FISH];
uint8_t fish_speed_counter = 0;  // Counter to slow down fish movement

#define MIN_MOVE_INTERVAL 30     // Minimum frames before a fish changes direction
#define MAX_MOVE_INTERVAL 120    // Maximum frames before a fish changes direction
#define FISH_TILE_INDEX 2

void init_fish(void) {
    // Load the normal guppy and hungry guppy tiles into VRAM
    set_sprite_data(FISH_TILE_INDEX, guppy_sprite_TILE_COUNT, guppy_sprite_tiles);
    set_sprite_data(FISH_TILE_INDEX + 2, hungry_guppy_sprite_TILE_COUNT, hungry_guppy_sprite_tiles);

    for (uint8_t i = 0; i < MAX_FISH; i++) {
        Fish* fish = &fish_list[i];
        fish->x = (uint8_t)(rand() % SCREENWIDTH);
        fish->y = (uint8_t)(rand() % SCREENHEIGHT);
        fish->sprite_id = allocate_sprite();
        fish->hunger_timer = INITIAL_HUNGER;
        fish->alive = true;

        // Initialize fish movement direction and random movement timer
        fish->dx = (rand() % 3) - 1;  // -1, 0, or 1
        fish->dy = (rand() % 3) - 1;  // -1, 0, or 1
        fish->movement_timer = (rand() % (MAX_MOVE_INTERVAL - MIN_MOVE_INTERVAL + 1)) + MIN_MOVE_INTERVAL;  // Random interval

        // Use metasprite for the fish sprite
        move_metasprite(guppy_sprite_metasprites[0], FISH_TILE_INDEX, fish->sprite_id, fish->x, fish->y);  // guppy_metasprites[0] is the first frame
    }
}

void update_fish(void) {
    fish_speed_counter++;  // Increment speed counter every frame

    for (uint8_t i = 0; i < MAX_FISH; i++) {
        Fish* fish = &fish_list[i];
        if (fish->alive) {
            // Only update movement every few frames to slow down fish
            if (fish_speed_counter % 4 == 0) {
                move_fish(fish);
            }

            if (fish->hunger_timer > 0) {
                fish->hunger_timer--;
            } else {
                fish->alive = false;
                hide_sprite(fish->sprite_id);
                // Maybe play a death animation or sound
            }

            if (food_near_fish(fish)) {
                fish->hunger_timer = INITIAL_HUNGER;
                fish->coin_fullness++;
                if (fish->coin_fullness >= COIN_FULLNESS_LIMIT) {
                    fish->coin_fullness = 0;
                    spawn_coin(fish->x, fish->y);
                }
            }
        }
    }
}

void move_fish(Fish* fish) {
    // If movement timer has expired, choose a new direction
    if (fish->movement_timer == 0) {
        fish->dx = (rand() % 3) - 1;  // New direction: -1, 0, or 1
        fish->dy = (rand() % 3) - 1;  // New direction: -1, 0, or 1
        // Set a new random movement interval
        fish->movement_timer = (rand() % (MAX_MOVE_INTERVAL - MIN_MOVE_INTERVAL + 1)) + MIN_MOVE_INTERVAL;
    } else {
        fish->movement_timer--;  // Decrease the timer
    }

    // Slow down the fish: update position only every few frames (already handled by `fish_speed_counter`)

    // Boundary checks to prevent fish from going off-screen
    if (fish->x + fish->dx >= SCREENWIDTH) {
        fish->dx = -1;  // Change direction to left
    } else if (fish->x + fish->dx < 8) {
        fish->dx = 1;   // Change direction to right
    } else {
        fish->x += fish->dx;  // Move fish horizontally
    }

    if (fish->y + fish->dy >= SCREENHEIGHT) {
        fish->dy = -1;  // Change direction to up
    } else if (fish->y + fish->dy < 16) {
        fish->dy = 1;   // Change direction to down
    } else {
        fish->y += fish->dy;  // Move fish vertically
    }

    // Update sprite position
    move_metasprite(guppy_sprite_metasprites[0], FISH_TILE_INDEX, fish->sprite_id, fish->x, fish->y);  // guppy_metasprites[0] is the first frame
}
