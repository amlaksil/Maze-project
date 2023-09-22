#include "../headers/headers.h"

/**
 * setup - Initializes the game context and sets up the player.
 *
 * @resources: Pointer to the game_resources_t struct representing
 * the game resources.
 */
void setup(game_resources_t *resources)
{
	resources->player.x = WINDOW_WIDTH / 2;
	resources->player.y = WINDOW_HEIGHT / 2;
	resources->player.width = 1;
	resources->player.height = 30;
	resources->player.turn_direction = 0;
	resources->player.walk_direction = 0;
	resources->player.rotation_angle = PI / 2;
	resources->player.walk_speed = 100;
	resources->player.turn_speed = 45 * (PI / 180);
	load_textures(resources);
}

/**
 * handle_keyboard_input - Handles keyboard input for the game.
 *
 * @resource: Pointer to the game_resource_t struct representing
 * the game resource.
 */
void handle_keyboard_input(game_resources_t *resource)
{
	SDL_Event event;

	/*
	 * Loop through all pending events in the event queue.
	 * Until it becomes empty. This is useful senarios
	 * where multiple events are generated at the same time.
	 */
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			resource->context.game_is_running = false;
			break;
		case SDL_KEYDOWN:
			handle_sdl_keydown(resource, &event);
			break;
		case SDL_KEYUP:
			handle_sdl_keyup(resource, &event);
			break;
		}
	}

	/*
	 * Ensure that the player doesn't move when conflicting key are pressed
	 * simultaneously. Hence, the walk_direction and turn_direction limits
	 * are set to -1, 0, or 1.
	 */
	if (resource->player.walk_direction > 1)
		resource->player.walk_direction = 1;
	if (resource->player.walk_direction < -1)
		resource->player.walk_direction = -1;
	if (resource->player.turn_direction > 1)
		resource->player.turn_direction = 1;
	if (resource->player.turn_direction < -1)
		resource->player.turn_direction = -1;
}
/**
 * update - Updates the game state and performs necessary operations.
 *
 * @resources: Pointer to the game_resource_t struct representing the
 * game resource.
 * @map: An instance of the map_t struct representing map data.
 */
void update(game_resources_t *resources, map_t *map)
{
	int time_to_wait;
	float delta_time;

	/* Calculate the remaining time to wait for the desired frame rate */
	time_to_wait = FRAME_TARGET_TIME - (
			SDL_GetTicks() - resources->context.last_frame_time);

	/*
	 * If the remaining time is positive and within the target frame time,
	 * delay the execution to maintain the desired frame rate.
	 */
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}
	/*
	 * Compute the delta time to be used as an update factor/
	 * when changing game objects.
	 */
	delta_time = (SDL_GetTicks() - resources->context.last_frame_time) / 1000.0f;

	/* Update the last frame time to the current time */
	resources->context.last_frame_time = SDL_GetTicks();

	/* Perform player movement based on the delta time */
	move_player(delta_time, &(resources->player), map);

	/* Cast rays for raycasting in the game */
	cast_all_rays(&(resources->player), map);
}
/**
 * render - Renders the game scene and displays it on the screen.
 * @resources: Pointer to the game_resources_t struct representing the
 * game resources.
 * @map: An instance of the map_t struct representing map data.
 */
void render(game_resources_t *resources, map_t *map)
{
	fill_color_buffer(resources, 0xFF000000);
	render_textured_walls(resources);
	if (resources->enable_minimap)
	{
		render_map_tiles(resources, map);
		render_minimap_rays(resources);
		render_player_on_minimap(resources);
	}
	render_color_buffer(resources);
}
/**
 * main - The entry point of the game program.
 * @argc: The number of command-line arguments passed to the program.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on successful execution.
 *
 * Description: This is the main function that serves as the entry point
 * of the game. It is responsible for executing the program's logic and
 * controlling the program flow.
 *
 */
int main(int argc, char *argv[])
{
	game_resources_t resources;
	map_t *map;
	const char *map_file_path;

	/* Initialize SDL_image */
	IMG_Init(IMG_INIT_PNG);

	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./run-game <map_file_path>\n");
		return (EXIT_FAILURE);
	}
	map_file_path = argv[1];
	map = malloc(sizeof(map_t));
	parse_map_from_file(map_file_path, map);

	resources.enable_minimap = false;

	/* Initialize the game window and check if it was successful */
	resources.context.game_is_running = initialize_window(&resources);

	/* Set up the game context */
	setup(&resources);

	/* Main game loop */
	while (resources.context.game_is_running)
	{
		/* Handle keyboard input */
		handle_keyboard_input(&resources);

		/* Update the game state */
		update(&resources, map);

		/* Render the game scene */
		render(&resources, map);
	}
	free(map);
	destroy_window(&resources);  /* Destroy the game window */

	return (EXIT_SUCCESS);
}
