#include "../headers/headers.h"

/**
 * initialize_window - Initializes the SDL window and related resources.
 * @resources: Pointer to the game_resource_t struct representing the
 * game resource.
 *
 * Return: True if initialization is successful, false otherwise.
 */
bool initialize_window(game_resources_t *resources)
{
	SDL_DisplayMode mode;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) /*SDL_INIT_VIDEO */
	{
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return (false);
	}
	if (SDL_GetCurrentDisplayMode(0, &mode) != 0)
		return (false);
	resources->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_RESIZABLE);
	if (!resources->window)
	{
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		return (false);
	}
	resources->renderer = SDL_CreateRenderer(resources->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!resources->renderer)
	{
		fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
		return (false);
	}
	SDL_SetRenderDrawBlendMode(resources->renderer, SDL_BLENDMODE_BLEND);
	resources->color_buffer = malloc(sizeof(color_t) * WINDOW_WIDTH *
			WINDOW_HEIGHT);
	if (!resources->color_buffer)
	{
		fprintf(stderr, "Unable to allocate memory for color buffer\n");
		return (false);
	}
	resources->color_buffer_texture = SDL_CreateTexture(resources->renderer,
			SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!resources->color_buffer_texture)
	{
		fprintf(stderr, "Error creating color buffer texture: %s\n", SDL_GetError());
		return (false);
	}
	return (true);
}

/**
 * destroy_window - Clean up and destroy the window resources
 *
 * @resources: Pointer to the game_resource_t struct representing the
 * game resource.
 *
 * Description: This function frees the color buffer, destroys the
 * color buffer texture, renderer, window, and quits SDL.
 */
void destroy_window(game_resources_t *resources)
{
	free_textures(resources);
	free(resources->color_buffer);
	SDL_DestroyTexture(resources->color_buffer_texture);
	SDL_DestroyRenderer(resources->renderer);
	SDL_DestroyWindow(resources->window);
	SDL_Quit();
}

/**
 * fill_color_buffer - Fills the color buffer with a specified color.
 *
 * @resources: Pointer to the game_resource_t struct representing
 * the game resource.
 * @color: The color value to fill the buffer with.
 *
 * Description: This function sets each pixel in the color buffer to the
 * specified color value, effectively clearing the previous contents.
 * The color buffer represents the color values of each pixel in the
 * window or screen.
 */
void fill_color_buffer(game_resources_t *resources, color_t color)
{
	int i;

	for (i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
	{
		resources->color_buffer[i] = color;
	}
}
/**
 * render_color_buffer - Updates the color buffer texture and renders
 * it to the screen.
 *
 * @resources: Pointer to the game_resource_t struct representing the
 * game resource.
 *
 * Description: This function updates the color buffer texture with the
 * contents of the color buffer, renders the color buffer texture onto
 * the renderer, and presents it on the screen.
 * It is responsible for displaying the rendered frame to the user.
 */
void render_color_buffer(const game_resources_t *resources)
{
	SDL_UpdateTexture
		(
		 resources->color_buffer_texture,
		 NULL,
		 resources->color_buffer,
		 (int)(WINDOW_WIDTH * sizeof(color_t))
		 );
	SDL_RenderCopy(resources->renderer, resources->color_buffer_texture,
			NULL, NULL);
	SDL_RenderPresent(resources->renderer);
}
/**
 * draw_pixel - Sets the color of a pixel in the color buffer.
 *
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 * @color: The color of the pixel.
 * @resources: Pointer to the game_resource_t struct representing
 * the game resource.
 */
void draw_pixel(int x, int y, color_t color, game_resources_t *resources)
{
	int index = (WINDOW_WIDTH * y) + x;

	if (index >= 0 && index < (WINDOW_WIDTH * WINDOW_HEIGHT))
		resources->color_buffer[index] = color;
}
