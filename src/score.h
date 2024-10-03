#pragma once
#include <stdbool.h>

/**
 * The starting bank balance of the player.
 */
#define STARTING_BALANCE (100)

typedef struct score_t
{
    int money;

    int last_money;
} score_t;

/**
 * The different types of food available for purchase.
 *
 * \note The values are the prices of the food.
 */
typedef enum score_food_t
{
    SCORE_FOOD_BASIC = 2,
} score_food_t;

/**
 * The value of a coin when collected.
 *
 * \note This is the value of a single coin.
 * The enum value is  also the value of the coin.
 */
typedef enum score_coin_t
{
    SCORE_COIN_BASIC = 10,
} score_coin_t;

extern void
score_init(score_t *score);

extern void
score_render(score_t *score);

extern void
score_buy_food(score_t *score, score_food_t food);

extern bool
score_can_afford_food(score_t *score, score_food_t food);

extern void
score_collect_coin(score_t *score, score_coin_t coin);

extern void
score_tile_base(int number_base, int symbol_base);
