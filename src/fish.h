#ifndef FISH_H
#define FISH_H

#include <gb/gb.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_FISH 5
#define TILE_FISH 2
#define INITIAL_HUNGER 59.7 * 30 // 30 seconds
#define COIN_FULLNESS_LIMIT 3
#define FISH_MOVE_INTERVAL 60 // Number of frames before a fish changes direction

typedef struct
{
    uint8_t x, y;
    uint8_t sprite_id;
    uint16_t hunger_timer;
    uint8_t coin_fullness;
    bool alive;
    int8_t dx, dy;           // Current direction of movement
    uint16_t movement_timer; // Timer to determine when to change direction
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
