// utils.c
#include "utils.h"
#include <limits.h> // For INT16_MIN
#include <stdint.h>

inline uint8_t
abs_val(int16_t x)
{
    if (x < 0)
    {
        if (x == INT16_MIN)
        {
            // INT16_MIN cannot be represented as a positive 16-bit integer.
            // Clamp to maximum uint8_t value.
            return 255;
        }
        return (uint8_t)(-x);
    }
    return (uint8_t)x;
}

inline uint8_t
manhattan_distance(int16_t delta_x, int16_t delta_y)
{
    uint8_t abs_x = abs_val(delta_x);
    uint8_t abs_y = abs_val(delta_y);

    // Prevent overflow by clamping the sum to 255
    if ((uint16_t)abs_x + (uint16_t)abs_y > 255)
    {
        return 255;
    }
    return abs_x + abs_y;
}

inline int8_t
get_direction(int16_t from, int16_t to)
{
    if (from < to)
    {
        return 1; // Move right/up
    }
    else if (from > to)
    {
        return -1; // Move left/down
    }
    else
    {
        return 0; // No movement
    }
}
