#include "score.h"
#include <gb/drawing.h>
#include <string.h>

void
score_init(score_t *score)
{
    memset(score, 0, sizeof(score_t));

    score->money = STARTING_BALANCE;
}

void
score_render(score_t *score)
{
    if (score->last_money == score->money)
        return;

    gotogxy(0, 0);
    gprintf("     ");
    gotogxy(0, 0);
    gprintf("$%d", score->money);

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
