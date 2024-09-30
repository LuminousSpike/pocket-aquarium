#ifndef FISH_H
#define FISH_H

#include <gb/gb.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_FISH 10
#define MAX_FISH_SPEED 3
#define TILE_FISH 2
#define INITIAL_HUNGER 0xFF
#define COIN_FULLNESS_LIMIT 3
#define HUNGER_THRESHOLD 100

typedef enum
{
    FISH_STATE_NORMAL,
    FISH_STATE_HUNGRY,
    FISH_STATE_DEAD
} FishState;

typedef struct
{
    FishState state;
    uint8_t x, y;
    uint8_t sprite_id;
    uint8_t hunger_timer;
    uint8_t coin_fullness;
    bool has_found_food;
    int8_t dx, dy, dspeed;  // Current direction of movement
    uint8_t movement_timer; // Timer to determine when to change direction
} Fish;

extern Fish fish_list[MAX_FISH];

void
init_fish(void);
void
update_fish(void);
void
move_fish(Fish *fish);

uint8_t
allocate_sprite(void);

#endif // FISH_H
