#include "../headers/headers.h"

/**
 * is_ray_facing_down - Checks if the ray is facing downward.
 * @angle: The angle of the ray.
 *
 * Return: true if the ray is facing downward, false otherwise.
 */
bool is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < PI);
}
/**
 * is_ray_facing_up - Checks if the ray is facing upward
 * @angle: The angle of the ray.
 *
 * Return: true if the ray is facing upward, false otherwise.
 */

bool is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}
/**
 * is_ray_facing_right - Checks if the ray is facing right.
 * @angle: The angle of the ray.
 *
 * Return: true if the ray is facing right, false otherwise.
 */

bool is_ray_facing_right(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}
/**
 * is_ray_facing_left - Checks if a ray is facing left.
 * @angle: The angle of the ray.
 *
 * Return: true if the ray is facing left, false otherwise.
 */
bool is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}

/**
 * distance_between_points - calculates the Euclidean distance between
 * two points in a two-dimensional coordinate system
 * @x1: x coordinate of first point
 * @y1: y coordinate of first point
 * @x2: x coordinate of second point
 * @y2: y coordinate of second point
 *
 * Return: the distance between two points
 */
int distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
