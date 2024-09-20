// cursor.h
#ifndef CURSOR_H
#define CURSOR_H

#include <gb/gb.h>

// Cursor structure
typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t sprite_id;
} Cursor;

extern Cursor cursor; // Declare the cursor object globally

void
init_cursor(void);
void
move_cursor(void);
void
drop_food(void);

#endif // CURSOR_H
