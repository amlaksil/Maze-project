#include "../headers/headers.h"

/**
 * darken_color_intensity - Darkens the intensity of the specified
 * color by the given factor.
 *
 * @color: Pointer to the color value to be modified.
 * @factor: The factor by which to darken the intensity of the color.
 */
void darken_color_intensity(color_t *color, float factor)
{
	color_t a, r, g, b;

	/* Extract the alpha component of the color */
	a = (*color & 0xFF000000);

	/* Extract the red component of the color and darken it */
	r = (*color & 0x00FF0000) * factor;

	/* Extract the green component of the color and darken it */
	g = (*color & 0x0000FF00) * factor;

	/* Extract the blue component of the color and darken it */
	b = (*color & 0x000000FF) * factor;

	/* Combine the modified color components back into the color value */
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}
/**
 * render_floor - Renders the floor on the screen beneath the current wall.
 *
 * This function calculates the distance and ratio based on
 * the player's height and the y-position. It then calculates the texture
 * offsets using the distance, ray angle, and player's position. The function
 * retrieves the color from the texture buffer based on the texture offsets.
 * Finally, it calls the draw_pixel function to draw the pixel on the screen.
 *
 * @wall_bottom: The bottom position of the current wall on the screen.
 * @pixel_color: Pointer to the variable that will be updated with
 * the color of the current pixel.
 * @column: The current column being rendered.
 * @inst: Pointer to the game_resource_t struct representing the game resource.
 */
void render_floor(
	int wall_bottom, color_t *pixel_color,
	int column, game_resources_t *inst)
{
	int row, texture_height, texture_width,
		texture_offset_y, texture_offset_x;
	float distance, ratio;

	/* Get the dimensions of the floor texture */
	texture_width = inst->wall_textures[FLOOR_TEXTURE_INDEX].width;
	texture_height = inst->wall_textures[FLOOR_TEXTURE_INDEX].height;


	for (row = wall_bottom - 1; row < WINDOW_HEIGHT; row++)
	{
		ratio = inst->player.height / (row - WINDOW_HEIGHT / 2);
		distance = (ratio * DISTANCE_TO_PROJ_PLANE) /
			cos(inst->player.rays[column].ray_angle -
			    inst->player.rotation_angle);
		texture_offset_y = floor(
			(distance * sin(inst->player.rays[column].ray_angle)) +
			inst->player.y);
		texture_offset_x = floor(
			(distance * cos(inst->player.rays[column].ray_angle)) +
			inst->player.x);

		/* Apply wrapping texture offsets based on texture dimensions */
		if (texture_width > 0)
			texture_offset_x = (texture_offset_x % texture_width + texture_width) %
				texture_width;
		if (texture_height > 0)
			texture_offset_y = (texture_offset_y % texture_height + texture_height) %
				texture_height;
		*pixel_color = inst->wall_textures[FLOOR_TEXTURE_INDEX].texture_buffer[(
				texture_width * texture_offset_y) + texture_offset_x];
		draw_pixel(column, row, *pixel_color, inst);
	}
}

/**
 * render_ceil - Renders the ceiling on the screen above the current wall.
 *
 * This function calculates the distance and ratio based on
 * the player's height and the y-position. It then calculates the texture
 * offsets using the distance, ray angle, and player->s position. The function
 * retrieves the color from the texture buffer based on the texture offsets.
 * Finally, it calls the draw_pixel function to draw the pixel on the screen.
 *
 * @wall_top: The top position of the current wall on the screen.
 * @pixel_color: Pointer to the variable that will be updated with
 * the color of the current pixel.
 * @column: The current column being rendered.
 * @inst: Pointer to the game_resource_t struct representing the game resource.
 */
void render_ceil(int wall_top, color_t *pixel_color,
		 int column, game_resources_t *inst)
{
	int row, texture_width, texture_height,
		texture_offset_y, texture_offset_x;
	float ratio, distance;

	texture_width = inst->wall_textures[CEILING_TEXTURE_INDEX].width;
	texture_height = inst->wall_textures[CEILING_TEXTURE_INDEX].height;


	for (row = 0; row < wall_top; row++)
	{
		ratio = inst->player.height / (row - WINDOW_HEIGHT / 2);
		distance = (ratio * DISTANCE_TO_PROJ_PLANE) /
			cos(inst->player.rays[column].ray_angle -
			    inst->player.rotation_angle);

		texture_offset_y = floor(
			(-distance * sin(inst->player.rays[column].ray_angle))
			+ inst->player.y);
		texture_offset_x = floor(
			(-distance * cos(inst->player.rays[column].ray_angle))
			+ inst->player.x);
		if (texture_width > 0)
			texture_offset_x = (texture_offset_x % texture_width +
					texture_width) % texture_width;
		if (texture_height > 0)
			texture_offset_y = (texture_offset_y % texture_height +
					texture_height) % texture_height;

		*pixel_color = inst->wall_textures[CEILING_TEXTURE_INDEX].texture_buffer[(
				texture_width * texture_offset_y) + texture_offset_x];
		draw_pixel(column, row, *pixel_color, inst);
	}
}

/**
 * render_textured_walls - Renders textured walls on the screen based on
 * raycasting calculations.
 *
 * @inst: Pointer to the game_resource_t struct representing the game resource.
 * This function calculates the wall height, texture offsets, and retrieves the
 * appropriate texture information to render the walls. It also handles drawing
 * the floor and ceiling, and applies darkening to the wall pixels if
 * necessary.
 */
void render_textured_walls(game_resources_t *inst)
{
	float perpendicular_distance;
	int wall_top, wall_bottom, texture_offset_x, texture_offset_y, wall_height,
	    distance_from_top, texture_index, texture_width, texture_height, col, x;
	color_t pixel_color;

	for (col = 0; col < NUM_RAYS; col++)
	{
		/* Perpendicular distance to avoid the fish-eye distortion */
		perpendicular_distance = inst->player.rays[col].distance * cos(
				inst->player.rays[col].ray_angle - inst->player.rotation_angle);
		if (perpendicular_distance > 0)
		{
			wall_height = (int)((TILE_SIZE / perpendicular_distance) *
					DISTANCE_TO_PROJ_PLANE); /* Projected wall height */
			wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
			wall_top = wall_top < 0 ? 0 : wall_top;
			wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);
			wall_bottom = wall_bottom > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom;
			texture_index = inst->player.rays[col].texture - 1;
			texture_width = inst->wall_textures[texture_index].width;
			texture_height = inst->wall_textures[texture_index].height;
			render_floor(wall_bottom, &pixel_color, col, inst);
			render_ceil(wall_top, &pixel_color, col, inst);
			if (inst->player.rays[col].was_hit_vertical) /* Texture offset for x-axis*/
				texture_offset_x = (int)inst->player.rays[col].wall_hit_y % TILE_SIZE;
			else
				texture_offset_x = (int)inst->player.rays[col].wall_hit_x % TILE_SIZE;
			for (x = wall_top; x < wall_bottom; x++) /* Render top to bottom */
			{
				distance_from_top = x + (wall_height / 2) - (WINDOW_HEIGHT / 2);
				texture_offset_y = distance_from_top * ((float)texture_height /
						wall_height);
				pixel_color = inst->wall_textures[texture_index].texture_buffer[(
						texture_width * texture_offset_y) + texture_offset_x];
				if (inst->player.rays[col].was_hit_vertical)
					darken_color_intensity(&pixel_color, 0.7);
				draw_pixel(col, x, pixel_color, inst);
			}
		}
	}
}

/**
 * render_map_tiles - Renders the grid-based map by drawing
 * tiles on the screen.
 *
 * @resources: Pointer to the game_resources_t struct representing the
 * game resources.
 * @map: An instance of the map_t struct representing map data.
 *
 * This function iterates over each tile in the map grid and renders it on
 * the screen using the appropriate color. The color of each tile is determined
 * by the get_tile_color function.
 *
 * The map tiles are rendered as rectangles on the screen, scaled based on
 * the MINIMAP_SCALE_FACTOR.
 */
void render_map_tiles(game_resources_t *resources, map_t *map)
{
	int tile_x, tile_y, i, j;
	color_t tile_color;

	if (!resources->enable_minimap)
		return; /* Exit the function early if rendering is disabled */

	for (i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (j = 0; j < MAP_NUM_COLS; j++)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			tile_color = get_tile_color(i, j, map);

			draw_rect(
					tile_x * MINIMAP_SCALE_FACTOR,
					tile_y * MINIMAP_SCALE_FACTOR,
					TILE_SIZE * MINIMAP_SCALE_FACTOR,
					TILE_SIZE * MINIMAP_SCALE_FACTOR,
					tile_color,
					resources
					);
		}
	}
}
