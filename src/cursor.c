#include "cursor.h"
#include "../res/cursor_sprite.h" // Include the cursor sprite data
#include "food.h"

#define FOOD_SPAWN_INTERVAL 30 // 0.5 seconds at ~59.7 FPS
#define CURSOR_TILE_INDEX 0

uint8_t
allocate_sprite(void);

Cursor cursor;
uint8_t food_spawn_timer = 0; // Timer to control the spawn rate of food
bool b_button_held = false;   // Flag to check if the B button was previously held

void
init_cursor(void)
{
    cursor.x = SCREENWIDTH / 2;
    cursor.y = SCREENHEIGHT / 2;
    cursor.sprite_id = allocate_sprite();

    // Load cursor sprite tiles into VRAM at the correct index
    set_sprite_data(CURSOR_TILE_INDEX, cursor_sprite_TILE_COUNT, cursor_sprite_tiles);

    // Use metasprite to position the 8x16 cursor sprite
    move_metasprite(cursor_sprite_metasprites[0], CURSOR_TILE_INDEX, cursor.sprite_id, cursor.x, cursor.y);
}

void
move_cursor(void)
{
    // Update cursor position based on input
    if (joypad() & J_LEFT && cursor.x - 8 > 0)
        cursor.x--;
    if (joypad() & J_RIGHT && cursor.x < SCREENWIDTH)
        cursor.x++;
    if (joypad() & J_UP && cursor.y > 16)
        cursor.y--;
    if (joypad() & J_DOWN && cursor.y < SCREENHEIGHT + 8)
        cursor.y++;

    // Update the metasprite position to move the 8x16 cursor
    move_metasprite(cursor_sprite_metasprites[0], CURSOR_TILE_INDEX, cursor.sprite_id, cursor.x, cursor.y);
}

void
drop_food(void)
{
    // Increment the spawn timer each frame
    food_spawn_timer++;

    // Check if the B button is pressed
    if (joypad() & J_B)
    {
        // If the B button was not previously held, spawn food instantly
        if (!b_button_held || food_spawn_timer >= FOOD_SPAWN_INTERVAL)
        {
            spawn_food(cursor.x, cursor.y); // Spawn food at the cursor position
            food_spawn_timer = 0;           // Reset the spawn timer after spawning food
            b_button_held = true;           // Mark that the B button is being held
        }
    }
    else
    {
        // Reset the timer and flag when the B button is released
        food_spawn_timer = 0;
        b_button_held = false;
    }
}
