#include "coin.h"
#include "../res/blank_tile.h"
#include "../res/coin_sprite.h"
#include "cursor.h"
#include "utils.h"
#include <gb/gb.h>
#include <rand.h>

#define COIN_TILE_INDEX 6

uint8_t
allocate_sprite(void);
void
free_sprite(uint8_t sprite_id);

Coin coin_list[MAX_COINS];
uint16_t player_coins = 0;
uint8_t coin_speed_counter = 0; // Counter to slow down the coin drop speed

void
init_coins(void)
{
    // Load the coin tiles into VRAM
    set_sprite_data(COIN_TILE_INDEX, coin_sprite_TILE_COUNT, coin_sprite_tiles);
    set_sprite_data(COIN_TILE_INDEX + 1, blank_tile_TILE_COUNT, blank_tile_tiles);

    // Initialize all coins in the pool as inactive
    for (uint8_t i = 0; i < MAX_COINS; i++)
    {
        Coin *coin = &coin_list[i];
        coin->active = false;
        coin->sprite_id = NO_SPRITE; // Indicate that the sprite is not used
    }
}

void
spawn_coin(uint8_t x, uint8_t y)
{
    // Look for an inactive coin in the pool
    for (uint8_t i = 0; i < MAX_COINS; i++)
    {
        Coin *coin = &coin_list[i];
        if (!coin->active)
        {
            // Allocate a sprite only when activating the coin
            coin->sprite_id = allocate_sprite();
            if (coin->sprite_id == NO_SPRITE)
            {
                return; // No available sprites, avoid crash
            }

            // Initialize the coin
            coin->x = x;
            coin->y = y;
            coin->active = true;

            // Set the coin's sprite tile
            set_sprite_data(COIN_TILE_INDEX, coin_sprite_TILE_COUNT, coin_sprite_tiles);
            move_metasprite(coin_sprite_metasprites[0], COIN_TILE_INDEX, coin->sprite_id, coin->x, coin->y);
            break;
        }
    }
}

void
update_coins(void)
{
    coin_speed_counter++; // Increment the counter every frame

    for (uint8_t i = 0; i < MAX_COINS; i++)
    {
        Coin *coin = &coin_list[i];

        // If the coin is active, make it fall down
        if (coin->active)
        {
            // Only update the coin's position every 6 frames (slowing it down)
            if (coin_speed_counter % 6 == 0)
            {
                // Make the coin fall down
                coin->y += COIN_SPEED;
            }

            // Check if the coin is off-screen
            if (coin->y >= SCREENHEIGHT)
            {
                // Deactivate the coin and free the sprite
                free_sprite(coin->sprite_id); // Free the sprite here
                coin->active = false;
                coin->sprite_id = NO_SPRITE; // Mark the sprite as unused
            }
            else
            {
                // Update the sprite's position
                move_metasprite(coin_sprite_metasprites[0], COIN_TILE_INDEX, coin->sprite_id, coin->x, coin->y);
            }

            // Check if the cursor is over the coin
            if (cursor_over_coin(coin))
            {
                // Deactivate the coin without checking for A button press
                free_sprite(coin->sprite_id); // Free the sprite here
                coin->active = false;
                coin->sprite_id = NO_SPRITE; // Mark the sprite as unused
                player_coins += COIN_VALUE;  // Increment the player's coin count
                play_sound(SOUND_COIN);      // Play sound for collecting the coin
            }
        }
    }
}

bool
cursor_over_coin(Coin *coin)
{
    extern Cursor cursor;

    // Calculate the center points of the cursor and the coin
    uint8_t cursor_center_x = cursor.x + 4; // Cursor width is 8, so center x is +4 pixels
    uint8_t cursor_center_y = cursor.y + 8; // Cursor height is 16, so center y is +8 pixels

    uint8_t coin_center_x = coin->x + 4; // Coin is 8x8, so center x is +4 pixels
    uint8_t coin_center_y = coin->y + 4; // Coin center y is +4 pixels

    // Use the ABS macro from utils.h to check if the centers are within 8 pixels
    // of each other
    return (ABS(cursor_center_x - coin_center_x) < 8 && ABS(cursor_center_y - coin_center_y) < 8);
}
