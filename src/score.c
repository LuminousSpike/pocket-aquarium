#include "score.h"
#include "../res/numbers.h"
#include <gb/drawing.h>
#include <gb/gb.h>
#include <string.h>

static int tile_base = 0;

void
score_tile_base(int base)
{
    tile_base = base;
}

void
score_init(score_t *score)
{
    memset(score, 0, sizeof(score_t));

    score->money = STARTING_BALANCE;
}

void
score_render(score_t *score)
{
    uint8_t scoredigits[5] = {0};
    const int score_x = 1;
    const int score_y = 1;

    if (score->last_money == score->money)
        return;

    int temp_money = score->money;
    for (int i = 4; i >= 0; i--)
    {
        scoredigits[i] = temp_money % 10;
        temp_money /= 10;
    }

    for (int i = 0; i < 5; i++)
    {
        /* TODO: Would prefer to use window, but this'll do...*/
        set_bkg_tile_xy(score_x + i, score_y, tile_base + scoredigits[i]);
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
