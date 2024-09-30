// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * @brief Computes the absolute value of a 16-bit signed integer.
 *
 * @param x The integer for which to compute the absolute value.
 * @return uint8_t The absolute value of x, clamped to 255 if necessary.
 */
uint8_t
abs_val(int16_t x);

/**
 * @brief Computes the Manhattan distance between two points.
 *
 * @param delta_x The difference in the x-coordinates.
 * @param delta_y The difference in the y-coordinates.
 * @return uint8_t The Manhattan distance, clamped to 255 if necessary.
 */
uint8_t
manhattan_distance(int16_t delta_x, int16_t delta_y);

/**
 * @brief Determines the direction from one coordinate to another.
 *
 * @param from The starting coordinate.
 * @param to The target coordinate.
 * @return int8_t -1 if moving left/down, 1 if moving right/up, 0 if no
 * movement.
 */
int8_t
get_direction(int16_t from, int16_t to);

#endif // UTILS_H
