#include "../headers/headers.h"

/**
 * render_minimap_rays - Renders a subset of rays on the minimap.
 *
 * @inst: Pointer to the game_resources_t struct representing
 * the game resources.
 *
 * Description: This function renders a subset of rays on the minimap by
 * drawing lines from the player's position to the wall hit position
 * of each ray.
 * It increments the loop index by 50 to draw only a few rays.
 */
void render_minimap_rays(game_resources_t *inst)
{
	int i;

	for (i = 0; i < NUM_RAYS; i += 50)
	{
		draw_line(
			inst->player.x * MINIMAP_SCALE_FACTOR,
			inst->player.y * MINIMAP_SCALE_FACTOR,
			inst->player.rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR,
			inst->player.rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR,
			0xFF0000FF,
			inst
			);
	}
}
/**
 * render_player_on_minimap - Renders the player's position on the minimap.
 *
 * @inst: Pointer to the game_resources_t struct representing
 * the game resources.
 *
 * Description: This function renders the player's position on the minimap as
 * a rectangle. The rectangle is drawn using the draw_rect function, which
 * takes the player's position, width, height, and a specified color.
 */
void render_player_on_minimap(game_resources_t *inst)
{
	draw_rect(
		inst->player.x * MINIMAP_SCALE_FACTOR,
		inst->player.y * MINIMAP_SCALE_FACTOR,
		inst->player.width * MINIMAP_SCALE_FACTOR,
		inst->player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF,
		inst
		);
}
/**
 * draw_line - Draw a line between two points using Bresenham's algorithm
 * @x0: X-coordinate of the start point
 * @y0: Y-coordinate of the start point
 * @x1: X-coordinate of the end point
 * @y1: Y-coordinate of the end point
 * @color: Color of the line
 * @resources: Pointer to the game_resources_t struct representing
 * the game resources.
 *
 * Description: This function draws a line between two points using
 * Bresenham's line drawing algorithm.
 * It calculates the incremental values for moving along the line and
 * calls the draw_pixel function to draw pixels at each position.
 */
void draw_line(
	int x0, int y0, int x1, int y1,
	color_t color, game_resources_t *resources)
{
	int delta_x, delta_y, longest_side_length, i;
	float x_inc, y_inc, current_x, current_y;

	/* diferences between start and end of the line */
	delta_x = (x1 - x0);
	delta_y = (y1 - y0);

	/* longest side of the line */
	longest_side_length = (
		abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

	/* find the increment values */
	x_inc = delta_x / (float)longest_side_length;
	y_inc = delta_y / (float)longest_side_length;
	/* start point */
	current_x = x0;
	current_y = y0;

	/* loop all the longest side until the end */
	for (i = 0; i < longest_side_length; i++)
	{
		/*
		 * Draw pixel, rounding the values to integer
		 * to get nearest pixel.
		 */
		draw_pixel(
			round(current_x), round(current_y), color, resources);

		/* increment the slope to get the next pixel */
		current_x += x_inc;
		current_y += y_inc;
	}
}

/**
 * draw_rect - Draws a rectangle on the screen.
 * @x: The x-coordinate of the top-left corner of the rectangle.
 * @y: The y-coordinate of the top-left corner of the rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 * @color: The color to be used for the rectangle.
 * @resources: Pointer to the game_resources_t struct representing
 * the game resources.
 *
 */
void draw_rect(
	int x, int y, int width, int height,
	color_t color, game_resources_t *resources)
{
	int i, j;

	for (i = x; i <= (x + width); i++)
	{
		for (j = y; j < (y + height); j++)
		{
			draw_pixel(i, j, color, resources);
		}
	}
}
