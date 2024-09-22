#ifndef COIN_H
#define COIN_H

#include <gb/gb.h>
#include <stdbool.h>
#include <stdint.h>

#include "score.h"

#define MAX_COINS 5
#define TILE_COIN 1
#define COIN_VALUE 1
#define SOUND_COIN 0
#define NO_SPRITE 255
#define COIN_SPEED 1 // The speed at which the coin falls (1 pixel per update)

typedef struct
{
    uint8_t x, y;
    uint8_t sprite_id;
    bool active;
} Coin;

extern Coin coin_list[MAX_COINS];
extern uint16_t player_coins;

void
init_coins(void);
void
spawn_coin(uint8_t x, uint8_t y);
void
update_coins(score_t *score);
bool
cursor_over_coin(Coin *coin);
void
play_sound(uint8_t sound_id);

#endif // COIN_H
