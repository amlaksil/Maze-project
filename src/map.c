#include "../headers/headers.h"

/**
 * parse_map_from_file - Parses map data from a file and stores it in
 * a map_t struct.
 *
 * @file_path: The path to the file containing the map data.
 * @map_data: A pointer to a map_t struct to store the parsed map data.
 *
 * Description: This function reads map data from a file specified by
 * @file_path and stores it in the provided map_t struct pointed to by
 * @map_data. The file should contain valid map data that can be parsed
 * and stored in the map_t struct. The function assumes that the @map_data
 * struct is already allocated and initialized.
 *
 */
void parse_map_from_file(const char *file_path, map_t *map_data)
{
	int i, j;
	FILE *file = fopen(file_path, "r");

	if (!file)
	{
		fprintf(stderr, "Unable to open file: %s\n", file_path);
		return;
	}
	for (i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (j = 0; j < MAP_NUM_COLS; j++)
		{
			fscanf(file, "%d", &map_data->map[i][j]);
		}
	}
	fclose(file);
}

/**
 * is_inside_map - Checks if a given coordinate is inside the map boundaries.
 *
 * @x: The x-coordinate of the point.
 * @y: The y-coordinate of the point.
 *
 * Return: Returns 1 if the point is inside the map, 0 otherwise.
 */
bool is_inside_map(float x, float y)
{
	/* Check if the point is within the map boundaries */
	return (x > 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <=
			MAP_NUM_ROWS * TILE_SIZE);
}

/**
 * map_has_wall_at - Checks if there is a wall at the specified coordinates.
 *
 * @x: The x-coordinate to check.
 * @y: The y-coordinate to check.
 * @map_data: An instance of the map_t struct representing map data.
 *
 * Return: True if there is a wall at the specified coordinates, false
 * otherwise.
 */
bool map_has_wall_at(float x, float y, map_t *map_data)
{
	int map_grid_index_x, map_grid_index_y;

	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >=
	    MAP_NUM_ROWS * TILE_SIZE)
		return (true);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);

	return (map_data->map[map_grid_index_y][map_grid_index_x] != 0);
}

/**
 * get_map_at - Retrieves the value at the specified indices in the map array.
 * @i: The row index in the map array.
 * @j: The column index in the map array.
 * @map_data: An instance of the map_t struct representing map data.
 *
 * Return: The value at the specified position in the map array.
 */
int get_map_at(int i, int j, map_t *map_data)
{
	return (map_data->map[i][j]);
}

/**
 * get_tile_color - Retrieves the color for a given tile in the map.
 * @row: The row index of the tile in the map grid.
 * @col: The column index of the tile in the map grid.
 * @map_data: An instance of the map_t struct representing map data.
 *
 * Return: The color (color_t) assigned to the tile.
 */
color_t get_tile_color(int row, int col, map_t *map_data)
{
	return (map_data->map[row][col] != 0 ? 0xFFFFFFFF : 0x00000000);
}
