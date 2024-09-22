#include "score.h"
#include "../res/numbers.h"
#include <gb/drawing.h>
#include <gb/gb.h>
#include <stdint.h>
#include <string.h>

static uint16_t numbers_base = 0;
static uint16_t symbols_base = 0;

void
score_tile_base(int numbers, int symbols)
{
    if (numbers >= 0)
        numbers_base = (uint16_t)numbers;
    if (symbols >= 0)
        symbols_base = (uint16_t)symbols;
}

void
score_init(score_t *score)
{
    memset(score, 0, sizeof(score_t));

    score->money = STARTING_BALANCE;
}

#define SCORE_MAX_DIGITS (3)

void
score_render(score_t *score)
{
    uint8_t scoredigits[SCORE_MAX_DIGITS] = {0};
    const int score_x = 1;
    const int score_y = 1;

    if (score->last_money == score->money)
        return;

    int temp_money = score->money;
    for (int i = (SCORE_MAX_DIGITS - 1); i >= 0; i--)
    {
        scoredigits[i] = temp_money % 10;
        temp_money /= 10;
    }

    /* Location of the money symbol */
    set_bkg_tile_xy(score_x, score_y, symbols_base + 0);

    for (int i = 0; i < SCORE_MAX_DIGITS; i++)
    {
        const uint8_t x_start = score_x + 1; /* 1 is the money symbol */

        /* TODO: Would prefer to use window, but this'll do...*/
        set_bkg_tile_xy(x_start + i, score_y, numbers_base + scoredigits[i]);
    }

    score->last_money = score->money;
}

void
score_buy_food(score_t *score, score_food_t food)
{
    if (score_can_afford_food(score, food))
        score->money -= food;
}

bool
score_can_afford_food(score_t *score, score_food_t food)
{
    return score->money >= food;
}

void
score_collect_coin(score_t *score, score_coin_t coin)
{
    score->money += coin;
}
