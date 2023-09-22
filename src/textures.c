#include "../headers/headers.h"

static const char *texture_file_names[NUM_TEXTURES] = {
	"./images/redbrick.png",
	"./images/mossystone.png",
	"./images/graystone.png",
	"./images/wood.png",
	"./images/colorstone.png",
	"./images/bluestone.png",
};
/**
 * get_texture_rgba_values - Retrieves the RGBA pixel values from a surface.
 * @surface: The input SDL_Surface to extract the pixel values from.
 * @rgba_buffer: A pointer to an unsigned int buffer to store the
 * RGBA pixel values.
 *
 * Description: This function converts the @surface to the RGBA32 format,
 * locks the surface, and copies the RGBA pixel values into the @rgba_buffer.
 * The @rgba_buffer should be preallocated with enough memory to store the
 * pixel values. The surface is then unlocked and freed.
 *
 */
void get_texture_rgba_values(SDL_Surface *surface, color_t *rgba_buffer)
{
	color_t *pixels;
	int num_pixels;
	SDL_Surface *converted_surface;

	converted_surface = SDL_ConvertSurfaceFormat(
			surface, SDL_PIXELFORMAT_RGBA32, 0);
	if (converted_surface != NULL)
	{
		SDL_LockSurface(converted_surface);

		pixels = (color_t *)converted_surface->pixels;
		num_pixels = converted_surface->w * converted_surface->h;
		memcpy(rgba_buffer, pixels, num_pixels * sizeof(color_t));

		SDL_UnlockSurface(converted_surface);
		SDL_FreeSurface(converted_surface);
	}
	else
	{
		fprintf(stderr, "Error converting surface format: %s\n",
				SDL_GetError());
	}
}

/**
 * load_textures - Loads textures from image files and retrieves
 * RGBA pixel values.
 * @inst: Pointer to the game_resources_t struct that holds the texture data.
 *
 * Description: This function loads textures from image files specified in the
 * texture_file_names array. It converts the loaded surfaces to the RGBA32
 * format, creates SDL textures from the surfaces, and retrieves RGBA pixel
 * values into the texture_buffer field of the wall_textures array in the
 * game_resources_t struct.
 *
 */
void load_textures(game_resources_t *inst)
{
	color_t num_pixels;
	SDL_Surface *converted_surface, *image_surface;
	SDL_Renderer *renderer;
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
	{
		image_surface = IMG_Load(texture_file_names[i]);
		if (image_surface != NULL)
		{
			inst->wall_textures[i].width = image_surface->w;
			inst->wall_textures[i].height = image_surface->h;
			/* Convert surface to RGBA32 format */
			converted_surface = SDL_ConvertSurfaceFormat(image_surface,
					SDL_PIXELFORMAT_RGBA32, 0);
			SDL_FreeSurface(image_surface);
			image_surface = converted_surface;
			renderer = inst->renderer;
			inst->wall_textures[i].sdl_texture =
				SDL_CreateTextureFromSurface(renderer, image_surface);
			/* Convert pixel data to RGBA32 format */
			num_pixels = image_surface->w * image_surface->h;
			inst->wall_textures[i].texture_buffer = (color_t *)malloc(
					num_pixels * sizeof(color_t));
			if (inst->wall_textures[i].texture_buffer != NULL)
			{
				get_texture_rgba_values(
						image_surface, inst->wall_textures[i].texture_buffer);
			}
			else
				fprintf(stderr, "Error allocating memory for texture buffer\n");
			SDL_FreeSurface(image_surface);
		}
		else
		{
			fprintf(stderr, "Error loading texture %s: %s\n",
					texture_file_names[i], IMG_GetError());
		}
	}
}
/**
 * free_textures - Frees the textures and texture buffers in the
 * game_resources_t struct.
 * @inst: Pointer to the game_resources_t struct containing the texture data.
 *
 * Description: This function frees the SDL textures and texture buffers in
 * the wall_textures array of the game_resources_t struct. It iterates through
 * each texture, destroys the SDL texture using SDL_DestroyTexture, and frees
 * the texture buffer using free. It also sets the corresponding pointers to
 * NULL to indicate that the resources have been freed.
 *
 */
void free_textures(game_resources_t *inst)
{
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
	{
		if (inst->wall_textures[i].sdl_texture != NULL)
		{
			SDL_DestroyTexture(inst->wall_textures[i].sdl_texture);
			inst->wall_textures[i].sdl_texture = NULL;
		}

		if (inst->wall_textures[i].texture_buffer != NULL)
		{
			free(inst->wall_textures[i].texture_buffer);
			inst->wall_textures[i].texture_buffer = NULL;
		}
	}
}
