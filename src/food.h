#ifndef FOOD_H
#define FOOD_H

#include "fish.h"
#include <gb/gb.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_FOOD 5
#define TILE_FOOD 2
#define NO_SPRITE 255
#define FOOD_SPEED 1 // Speed at which the food pellet drops

#define GRID_SIZE 16
#define GRID_WIDTH (SCREENWIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREENHEIGHT / GRID_SIZE)

typedef struct
{
    uint8_t x, y;
    uint8_t sprite_id;
    bool active;
} Food;

extern Food food_list[MAX_FOOD];

void
init_food(void);
void
spawn_food(uint8_t x, uint8_t y);
void
update_food(void);
bool
food_near_fish(Fish *fish);

#endif // FOOD_H
