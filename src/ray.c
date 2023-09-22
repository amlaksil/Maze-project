#include "../headers/headers.h"

/**
 * find_horizontal_intersection - Finds the intersection point of a
 * horizontal ray with walls.
 * @ray_angle: The angle of the ray to find the intersection for.
 * @player: Pointer to the player_t struct.
 * @map: An instance of the map_t struct representing map data.
 *
 * Description: This function calculates the intersection point of a
 * horizontal ray with walls.
 * It iteratively checks for intersections until the intersection point
 * is outside the map bounds.
 * If a wall is found, the related variables and flags are updated accordingly.
 */
void find_horizontal_intersection(float ray_angle,
		player_t *player, map_t *map)
{
	float x, y, x_step, y_step, x_cord, y_cord;
	float next_horz_touch_x, next_horz_touch_y;

	/* Reset flags and variables related to horizontal intersection*/
	player->inst.found_horz_wall_hit = false;
	player->inst.horz_wall_hit_x = 0;
	player->inst.horz_wall_hit_y = 0;
	player->inst.horz_wall_texture = 0;

	y = floor(player->y / TILE_SIZE) * TILE_SIZE; /* Cal init intersection point*/
	y += is_ray_facing_down(ray_angle) ? TILE_SIZE : 0;
	x = player->x + (y - player->y) / tan(ray_angle);

	y_step = TILE_SIZE * (is_ray_facing_up(ray_angle) ? -1 : 1);
	x_step = TILE_SIZE / tan(ray_angle);
	x_step *= (is_ray_facing_left(ray_angle) && x_step > 0) ? -1 : 1;
	x_step *= (is_ray_facing_right(ray_angle) && x_step < 0) ? -1 : 1;
	next_horz_touch_x = x;
	next_horz_touch_y = y;

	while (is_inside_map(next_horz_touch_x, next_horz_touch_y))
	{
		x_cord = next_horz_touch_x; /* Check until the point is outside map bounds */
		y_cord = next_horz_touch_y + (is_ray_facing_up(ray_angle) ? -1 : 0);

		if (map_has_wall_at(x_cord, y_cord, map))
		{
			player->inst.horz_wall_hit_x = next_horz_touch_x;
			player->inst.horz_wall_hit_y = next_horz_touch_y;
			player->inst.horz_wall_texture = get_map_at(
					(int)floor(y_cord / TILE_SIZE),
					(int)floor(x_cord / TILE_SIZE), map);
			player->inst.found_horz_wall_hit = true;
			break;
		}
		next_horz_touch_x += x_step; /* Update next intersection */
		next_horz_touch_y += y_step;
	}
}

/**
 * find_vertical_intersection - Finds the intersection point of
 * a vertical ray with walls.
 * @ray_angle: The angle of the ray to find the intersection for.
 * @player: Pointer to the player_t struct.
 * @map: An instance of the map_t struct representing map data.
 *
 * Description: This function calculates the intersection point of
 * a vertical ray with walls. It iteratively checks for intersections
 * until the intersection point is outside the map bounds. If a wall is found,
 * the related variables and flags are updated accordingly.
 */
void find_vertical_intersection(float ray_angle, player_t *player, map_t *map)
{
	float x, y, x_step, y_step;
	float next_vert_touch_x, next_vert_touch_y, x_cord, y_cord;

	/* Reset the flags and variables related to vertical intersection */
	player->inst.found_vert_wall_hit = false;
	player->inst.vert_wall_hit_x = 0;
	player->inst.vert_wall_hit_y = 0;
	player->inst.vert_wall_texture = 0;

	x = floor(player->x / TILE_SIZE) * TILE_SIZE; /* Cal init intersection point*/
	x += is_ray_facing_right(ray_angle) ? TILE_SIZE : 0;
	y = player->y + (x - player->x) * tan(ray_angle);

	x_step = TILE_SIZE * (is_ray_facing_left(ray_angle) ? -1 : 1);
	y_step = TILE_SIZE * tan(ray_angle);
	y_step *= (is_ray_facing_up(ray_angle) && y_step > 0) ? -1 : 1;
	y_step *= (is_ray_facing_down(ray_angle) && y_step < 0) ? -1 : 1;

	next_vert_touch_x = x; /* Set initial values */
	next_vert_touch_y = y;


	while (is_inside_map(next_vert_touch_x, next_vert_touch_y))
	{
		x_cord = next_vert_touch_x + (is_ray_facing_left(ray_angle) ? -1 : 0);
		y_cord = next_vert_touch_y; /* Check until the point is outside map bounds */

		if (map_has_wall_at(x_cord, y_cord, map))
		{
			player->inst.vert_wall_hit_x = next_vert_touch_x;
			player->inst.vert_wall_hit_y = next_vert_touch_y;
			player->inst.vert_wall_texture = get_map_at(
					(int)floor(y_cord / TILE_SIZE),
					(int)floor(x_cord / TILE_SIZE), map);
			player->inst.found_vert_wall_hit = true;
			break;
		}
		next_vert_touch_x += x_step; /* Set initial values */
		next_vert_touch_y += y_step;
	}
}
/**
 * cast_ray - Casts a single ray and determines its intersection with walls.
 * @ray_angle: The angle of the ray to cast.
 * @column: The index of the column for the ray.
 * @player: Pointer to the player_t struct.
 * @map: An instance of the map_t struct representing map data.
 *
 * Description: This function casts a ray with the specified angle and
 * determines its intersection points with walls. It calculates the hit
 * distances between the player's position and the intersection points, and
 * updates the properties of the rays array for the given column.
 */
void cast_ray(float ray_angle, int column, player_t *player, map_t *map)
{
	float horz_hit_distance, vert_hit_distance;

	/* Ensure the ray_angle falls within the range of 0 to 360 degrees */
	normalize_angle(&ray_angle);

	find_horizontal_intersection(ray_angle, player, map);
	find_vertical_intersection(ray_angle, player, map);

	horz_hit_distance = player->inst.found_horz_wall_hit ? distance_between_points
		(player->x, player->y, player->inst.horz_wall_hit_x,
		 player->inst.horz_wall_hit_y) : FLT_MAX;
	vert_hit_distance = player->inst.found_vert_wall_hit ? distance_between_points
		(player->x, player->y, player->inst.vert_wall_hit_x,
		 player->inst.vert_wall_hit_y) : FLT_MAX;

	if (vert_hit_distance < horz_hit_distance) /*Choose the smallest hit dist*/
	{
		player->rays[column].distance = vert_hit_distance;
		player->rays[column].wall_hit_x = player->inst.vert_wall_hit_x;
		player->rays[column].wall_hit_y = player->inst.vert_wall_hit_y;
		player->rays[column].texture = player->inst.vert_wall_texture;
		player->rays[column].was_hit_vertical = true;
		player->rays[column].ray_angle = ray_angle;
	}
	else
	{

		player->rays[column].distance = horz_hit_distance;
		player->rays[column].wall_hit_x = player->inst.horz_wall_hit_x;
		player->rays[column].wall_hit_y = player->inst.horz_wall_hit_y;
		player->rays[column].texture = player->inst.horz_wall_texture;
		player->rays[column].was_hit_vertical = false;
		player->rays[column].ray_angle = ray_angle;
	}
}
/**
 * cast_all_rays - Casts rays for each column of the screen to
 * generate the 3D projection.
 * @player: Pointer to the player_t struct.
 * @map: An instance of the map_t struct representing map data.
 *
 */
void cast_all_rays(player_t *player, map_t *map)
{
	float ray_angle;
	int column;

	for (column = 0; column < NUM_RAYS; column++)
	{
		/* Calculate the ray_angle for the current column */
		ray_angle = player->rotation_angle + atan(
			(column - NUM_RAYS / 2) / DISTANCE_TO_PROJ_PLANE);

		/* Cast a ray with the calculated angle for the current column */
		cast_ray(ray_angle, column, player, map);
	}
}
