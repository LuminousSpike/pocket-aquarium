#include "food.h"
#include "../res/blank_tile.h"
#include "../res/food_sprite.h"
#include "fish.h"
#include "utils.h"
#include <gb/gb.h>
#include <rand.h>

#define FOOD_TILE_INDEX 4

uint8_t food_speed_counter = 0; // Counter to slow down food movement

uint8_t
allocate_sprite(void);
void
free_sprite(uint8_t sprite_id);

Food food_list[MAX_FOOD];

void
init_food(void)
{
    // Load the food pellet tiles into VRAM
    set_sprite_data(FOOD_TILE_INDEX, food_sprite_TILE_COUNT, food_sprite_tiles);
    set_sprite_data(FOOD_TILE_INDEX + 1, blank_tile_TILE_COUNT,
                    blank_tile_tiles);

    // Initialize all food pellets as inactive
    for (uint8_t i = 0; i < MAX_FOOD; i++)
    {
        Food *food = &food_list[i];
        food->active = false;
        food->sprite_id = NO_SPRITE;
    }
}

void
spawn_food(uint8_t x, uint8_t y)
{
    // Look for an inactive food pellet to spawn
    for (uint8_t i = 0; i < MAX_FOOD; i++)
    {
        Food *food = &food_list[i];
        if (!food->active)
        {
            // Allocate a sprite for the food pellet
            food->sprite_id = allocate_sprite();
            if (food->sprite_id == NO_SPRITE)
            {
                return;
            }

            // Initialize the food pellet
            food->x = x;
            food->y = y;
            food->active = true;

            // Set the food's sprite tile
            set_sprite_data(FOOD_TILE_INDEX, food_sprite_TILE_COUNT,
                            food_sprite_tiles);
            move_metasprite(food_sprite_metasprites[0], FOOD_TILE_INDEX,
                            food->sprite_id, food->x, food->y);
            break;
        }
    }
}

// Optimized update_food using proximity optimization
void
update_food(void)
{
    food_speed_counter++; // Increment speed counter every frame
    Food *food = &food_list[food_speed_counter % MAX_FOOD];

    // If the food is active, make it fall down
    if (food->active)
    {
        food->y += FOOD_SPEED;

        // Check if the food is off-screen
        if (food->y >= SCREENHEIGHT)
        {
            free_sprite(food->sprite_id);
            food->active = false;
            food->sprite_id = NO_SPRITE;
        }
        else
        {
            // Update the food's sprite position only if necessary
            move_metasprite(food_sprite_metasprites[0], FOOD_TILE_INDEX,
                            food->sprite_id, food->x, food->y);
        }
    }
}

bool
food_near_fish(Fish *fish)
{
    // Use direct proximity check instead of grid for simplicity
    for (uint8_t i = 0; i < MAX_FOOD; i++)
    {
        Food *food = &food_list[i];
        if (food->active)
        {
            // Use fast proximity check
            if (ABS(fish->x - food->x) <= 8 && ABS(fish->y - food->y) <= 8)
            {
                // If food is close to the fish, the fish eats it
                if (fish->is_hungry)
                {
                    free_sprite(food->sprite_id);
                    food->active = false;
                    food->sprite_id = NO_SPRITE;
                }
                return true;
            }
        }
    }
    return false;
}
