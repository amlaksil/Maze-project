#ifndef __MAZE_GAME__
#define __MAZE_GAME__

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define PI 3.14159265
#define TILE_SIZE 64
#define NUM_TEXTURES 6
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define NUM_RAYS WINDOW_WIDTH
#define FOV_ANGLE (60 * (PI / 180))
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define MAP_NUM_ROWS 13 /*13*/
#define MAP_NUM_COLS 20 /*20*/
#define FLOOR_TEXTURE_INDEX 4
#define CEILING_TEXTURE_INDEX 4
#define MINIMAP_SCALE_FACTOR 0.2
#define DISTANCE_TO_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))
typedef uint32_t color_t;
/*extern int map[MAP_NUM_ROWS][MAP_NUM_COLS];*/

/**
 * struct ray_s - Represents a ray used in raycasting.
 *
 * @ray_angle: The angle of the ray.
 * @wall_hit_x: The x-coordinate of the wall hit point.
 * @wall_hit_y: The y-coordinate of the wall hit point.
 * @distance: The distance from the ray's origin to the wall hit point.
 * @was_hit_vertical: Indicates whether the wall hit was vertical (true) or
 * horizontal (false).
 * @texture: The texture associated with the wall hit.
 */
typedef struct ray_s
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	bool was_hit_vertical;
	int texture;
} ray_t;

/**
 * struct wall_hit_data - Structure to hold wall hit data
 * @horz_wall_hit_x: X-coordinate of the horizontal wall hit
 * @horz_wall_hit_y: Y-coordinate of the horizontal wall hit
 * @vert_wall_hit_x: X-coordinate of the vertical wall hit
 * @vert_wall_hit_y: Y-coordinate of the vertical wall hit
 * @horz_wall_texture: Horizontal wall texture
 * @vert_wall_texture: Vertical wall texture
 * @found_horz_wall_hit: Flag indicating if a horizontal wall hit was found
 * @found_vert_wall_hit: Flag indicating if a vertical wall hit was found
 *
 * This structure encapsulates the variables related to wall hit information.
 */
typedef struct wall_hit_data
{
	float horz_wall_hit_x;
	float horz_wall_hit_y;
	float vert_wall_hit_x;
	float vert_wall_hit_y;
	int horz_wall_texture;
	int vert_wall_texture;
	bool found_horz_wall_hit;
	bool found_vert_wall_hit;
} wall_hit_data_t;

/**
 * struct map_s - Represents a map with integer values.
 *
 * @map: A 2D array representing the map.
 *       The first dimension represents the number of rows.
 *       The second dimension represents the number of columns.
 *       Elements of the map are of type int.
 *
 * Description: This struct defines a map with integer values arranged
 * in rows and columns. The map is represented by a 2D array.
 */
typedef struct map_s
{
	int map[MAP_NUM_ROWS][MAP_NUM_COLS];
} map_t;

/**
 * struct player_t - Represents a player in the game.
 *
 * @x: The x-coordinate of the player's position.
 * @y: The y-coordinate of the player's position.
 * @width: The width of the player's bounding box.
 * @height: The height of the player's bounding box.
 * @turn_direction: The player's turn direction
 * (-1 for left, 1 for right, 0 for no turn).
 * @walk_direction: The player's walk direction
 * (-1 for backward, 1 for forward, 0 for no walk).
 * @rotation_angle: The current rotation angle of the player.
 * @walk_speed: The speed at which the player walks.
 * @turn_speed: The speed at which the player turns.
 * @rays: An array of ray_t struct.
 * @inst: An instance of wall_hit_data_t struct.
 * @map_data: An instance of the map_t struct representing map data.
 */
typedef struct player_t
{
	float x;
	float y;
	float width;
	float height;
	int turn_direction;
	int walk_direction;
	float rotation_angle;
	float walk_speed;
	float turn_speed;
	ray_t rays[NUM_RAYS];
	wall_hit_data_t inst;
	map_t map_data;
} player_t;

/**
 * struct game_context_s - Represents the context of a game.
 *
 * @game_is_running: Boolean flag indicating whether the
 * game is currently running.
 * @last_frame_time: The timestamp of the last frame in milliseconds.
 * @rays: An array of ray_t struct.
 */
typedef struct game_context_s
{
	bool game_is_running;
	int last_frame_time;
	ray_t rays[NUM_RAYS];
} game_context_t;

/**
 * struct texture_s - Represents a texture in the game.
 *
 * @width: The width of the texture in pixels
 * @height: The height of the texture in pixels.
 * @texture_buffer: Pointer to the texture buffer storing pixel data.
 * @sdl_texture: Pointer to the SDL_Texture representing the texture.
 *
 * Description: The texture_t struct represents a texture used in the game.
 * It contains information about the SDL texture, such as its dimensions, and
 * a buffer that stores the pixel data of the texture. The pixel data is
 * typically in the RGBA32 format and can be accessed through the
 * texture_buffer field.
 */
typedef struct texture_s
{
	SDL_Texture *sdl_texture;
	int width;
	int height;
	color_t *texture_buffer;
} texture_t;

/**
 * struct game_resources_s - Structure to hold game resources.
 * @window: Pointer to the SDL_Window used for rendering.
 * @renderer: Pointer to the SDL_Renderer used for rendering.
 * @color_buffer: Pointer to the color buffer for pixel colors.
 * @color_buffer_texture: Pointer to the SDL_Texture representing
 * the color buffer.
 * @enable_minimap: A flag to enable or disable minimap.
 * @player: An instance of player_t struct.
 * @context: An instance of game_context_t struct.
 * @wall_textures: An array of texture_t structs representing the wall
 * textures in the game.
 *
 */
typedef struct game_resources_s
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	color_t *color_buffer;
	SDL_Texture *color_buffer_texture;
	bool enable_minimap;
	player_t player;
	game_context_t context;
	texture_t wall_textures[NUM_TEXTURES];
} game_resources_t;

bool initialize_window(game_resources_t *);
void setup(game_resources_t *);
void destroy_window(game_resources_t *);

void handle_keyboard_input(game_resources_t *);
void process_other_movement_keys(game_resources_t *, SDL_Event *);
void handle_sdl_keydown(game_resources_t *, SDL_Event *);
void handle_sdl_keyup(game_resources_t *, SDL_Event *);
void update(game_resources_t *, map_t *);
void draw_pixel(int, int, color_t, game_resources_t *);
void move_player(float, player_t *, map_t *);
void normalize_angle(float *);
void handle_wall_collision(player_t *, map_t *);
void cast_all_rays(player_t *, map_t *);
void cast_ray(float, int, player_t *, map_t *);
void find_horizontal_intersection(float, player_t *, map_t *);
void find_vertical_intersection(float, player_t *, map_t *);
void parse_map_from_file(const char *file_path, map_t *);
bool is_inside_map(float, float);
bool map_has_wall_at(float, float, map_t *);
int get_map_at(int, int, map_t *);
color_t get_tile_color(int, int, map_t *);

bool is_ray_facing_down(float);
bool is_ray_facing_up(float);
bool is_ray_facing_right(float);
bool is_ray_facing_left(float);
int distance_between_points(float, float, float, float);

void render(game_resources_t *, map_t *);
void fill_color_buffer(game_resources_t *, color_t);
void render_textured_walls(game_resources_t *);
void render_floor(int, color_t *, int, game_resources_t *);
void render_ceil(int, color_t *, int, game_resources_t *);
void darken_color_intensity(color_t *, float);
void render_map_tiles(game_resources_t *, map_t *);
void render_minimap_rays(game_resources_t *);
void render_player_on_minimap(game_resources_t *);
void draw_line(int, int, int, int, color_t, game_resources_t *);
void draw_rect(int, int, int, int, color_t, game_resources_t *);
void render_color_buffer(const game_resources_t *);

void get_texture_rgba_values(SDL_Surface *, color_t *);
void load_textures(game_resources_t *);
void free_textures(game_resources_t *);

#endif /* __MAZE_GAME__ */
