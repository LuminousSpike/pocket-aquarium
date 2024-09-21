#include "fish.h"
#include "../res/guppy_sprite.h"
#include "../res/hungry_guppy_sprite.h"
#include "../res/blank_tile.h"
#include "../res/guppy_sprite.h"
#include "../res/hungry_guppy_sprite.h"
#include "coin.h"
#include "food.h"
#include "utils.h"
#include <rand.h>

Fish fish_list[MAX_FISH];
uint8_t fish_speed_counter = 0; // Counter to slow down fish movement

#define MIN_MOVE_INTERVAL 30  // Minimum frames before a fish changes direction
#define MAX_MOVE_INTERVAL 120 // Maximum frames before a fish changes direction
#define FISH_TILE_INDEX 2

void init_fish(void) {
    // Load the normal guppy and hungry guppy tiles into VRAM
    set_sprite_data(FISH_TILE_INDEX, guppy_sprite_TILE_COUNT, guppy_sprite_tiles);
    set_sprite_data(FISH_TILE_INDEX + 2, hungry_guppy_sprite_TILE_COUNT, hungry_guppy_sprite_tiles);

    for (uint8_t i = 0; i < MAX_FISH; i++)
    {
        Fish *fish = &fish_list[i];
        fish->x = (uint8_t)(rand() % SCREENWIDTH);
        fish->y = (uint8_t)(rand() % SCREENHEIGHT);
        fish->sprite_id = allocate_sprite();
        fish->hunger_timer = INITIAL_HUNGER;
        fish->alive = true;
        fish->is_hungry = false;

        // Initialize fish movement direction and random movement timer
        fish->dx = (rand() % 3) - 1;
        fish->dy = (rand() % 3) - 1;
        fish->movement_timer = (rand() % (MAX_MOVE_INTERVAL - MIN_MOVE_INTERVAL + 1)) + MIN_MOVE_INTERVAL;

        // Set the sprite to the normal fish initially
        move_metasprite(guppy_sprite_metasprites[0], FISH_TILE_INDEX, fish->sprite_id, fish->x, fish->y);
    }
}



// Helper function to get the direction towards the nearest food
bool nearest_food_position(Fish* fish, int8_t* out_dx, int8_t* out_dy) {
    Food* nearest_food = NULL;
    uint16_t nearest_distance = 0xFFFF;  // Start with max distance

    for (uint8_t i = 0; i < MAX_FOOD; i++) {
        Food* food = &food_list[i];
        if (food->active) {
            uint16_t distance = ABS(fish->x - food->x) + ABS(fish->y - food->y);  // Manhattan distance
            if (distance < nearest_distance) {
                nearest_distance = distance;
                nearest_food = food;
            }
        }
    }

    if (nearest_food) {
        // Set the direction towards the nearest food
        *out_dx = (fish->x < nearest_food->x) ? 1 : (fish->x > nearest_food->x) ? -1 : 0;
        *out_dy = (fish->y < nearest_food->y) ? 1 : (fish->y > nearest_food->y) ? -1 : 0;
        return true;  // Food is found
    }
    return false;  // No food found
}

void update_fish(void) {
    fish_speed_counter++;

    for (uint8_t i = 0; i < MAX_FISH; i++) {
        Fish* fish = &fish_list[i];
        if (fish->alive) {
            // Slow down fish movement
            if (fish_speed_counter % 4 == 0) {
                if (fish->hunger_timer < HUNGER_THRESHOLD && nearest_food_position(fish, &(fish->dx), &(fish->dy))) {
                    move_fish(fish);  // Move towards food
                } else {
                    move_fish(fish);  // Move randomly
                }
            }

            // Decrease hunger timer
            if (fish->hunger_timer > 0) {
                fish->hunger_timer--;
            }
            else
            {
                fish->alive = false;
                hide_sprite(fish->sprite_id);
            }

            // Check if the fish has crossed the hunger threshold and update sprite if necessary
            bool was_hungry = fish->is_hungry;
            fish->is_hungry = (fish->hunger_timer < HUNGER_THRESHOLD);

            if (fish->is_hungry != was_hungry) {
                // Switch to the hungry sprite or normal sprite
                if (fish->is_hungry) {
                    move_metasprite(hungry_guppy_sprite_metasprites[0], FISH_TILE_INDEX + 1, fish->sprite_id, fish->x, fish->y);
                } else {
                    move_metasprite(guppy_sprite_metasprites[0], FISH_TILE_INDEX, fish->sprite_id, fish->x, fish->y);
                }
            }

            // Check if the fish is near food and eats it
            if (food_near_fish(fish)) {
                fish->hunger_timer = INITIAL_HUNGER;
                fish->coin_fullness++;
                if (fish->coin_fullness >= COIN_FULLNESS_LIMIT)
                {
                    fish->coin_fullness = 0;
                    spawn_coin(fish->x, fish->y);
                }
            }
        }
    }
}


void move_fish(Fish* fish) {
    if (fish->movement_timer == 0) {
        fish->dx = (rand() % 3) - 1;
        fish->dy = (rand() % 3) - 1;
        fish->movement_timer = (rand() % (MAX_MOVE_INTERVAL - MIN_MOVE_INTERVAL + 1)) + MIN_MOVE_INTERVAL;
    } else {
        fish->movement_timer--;
    }

    // Ensure the fish doesn't go off-screen
    if (fish->x + fish->dx >= SCREENWIDTH) {
        fish->dx = -1;
    } else if (fish->x + fish->dx < 8) {
        fish->dx = 1;
    } else {
        fish->x += fish->dx;
    }

    if (fish->y + fish->dy >= SCREENHEIGHT) {
        fish->dy = -1;
    } else if (fish->y + fish->dy < 16) {
        fish->dy = 1;
    } else {
        fish->y += fish->dy;
    }

    // Update sprite position based on hunger state
    if (fish->is_hungry) {
        move_metasprite(hungry_guppy_sprite_metasprites[0], FISH_TILE_INDEX + 1, fish->sprite_id, fish->x, fish->y);
    } else {
        move_metasprite(guppy_sprite_metasprites[0], FISH_TILE_INDEX, fish->sprite_id, fish->x, fish->y);
    }
}
