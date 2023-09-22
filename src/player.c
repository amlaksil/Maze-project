#include "../headers/headers.h"

/**
 * normalize_angle - Normalizes the angle to be within the range of -π to π.
 * @angle: Pointer to the angle to be normalized in radians.
 */
void normalize_angle(float *angle)
{
	*angle = remainder(*angle, 2 * PI);
	if (*angle < 0)
		*angle = 2 * PI + *angle;
}

/**
 * move_player - Moves the player based on the provided delta time.
 *
 * @delta_time: The time elapsed since the last frame update.
 * @player: Pointer to the player_t struct.
 * @map: An instance of the map_t struct representing map data.
 */
void move_player(float delta_time, player_t *player, map_t *map)
{
	float move_step, new_player_x, new_player_y;

	/* Update rotation angle */
	player->rotation_angle += player->turn_direction *
		player->turn_speed * delta_time;

	/* Check rotation angle is in a valid range */
	normalize_angle(&(player->rotation_angle));

	/* Determine the distance the player will move in each frame */
	move_step = player->walk_direction * player->walk_speed * delta_time;

	/* Calculate the potential new position of the player */
	new_player_x = player->x + cos(player->rotation_angle) * move_step;
	new_player_y = player->y + sin(player->rotation_angle) * move_step;

	if (!map_has_wall_at(new_player_x, new_player_y, map))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
	else
	{
		/*
		 * Handle collision (sliding along walls instead of
		 * just stop it)
		 */
		handle_wall_collision(player, map);
	}
}

/**
 * handle_wall_collision - Adjusts the player's position and
 * enables sliding along the walls.
 * @player: Pointer to the player_t struct.
 * @map: An instance of the map_t struct representing map data.
 *
 */
void handle_wall_collision(player_t *player, map_t *map)
{
	float slide_x, slide_y, slide_step;

	slide_step = 25; /* Adjust the slide step size as needed */

	/* Calculate the slide direction based on the player's angle */
	slide_x = cos(player->rotation_angle) * slide_step;
	slide_y = sin(player->rotation_angle) * slide_step;

	/* Try sliding the player along the X-axis */
	if (!map_has_wall_at(player->x + slide_x, player->y, map))
	{
		player->x += slide_x;
	}
	/* Try sliding the player along the Y-axis */
	if (!map_has_wall_at(player->x, player->y + slide_y, map))
	{
		player->y += slide_y;
	}
}
