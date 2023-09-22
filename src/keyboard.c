#include "../headers/headers.h"

/**
 * handle_sdl_keydown - Handles keyboard input for the game.
 *
 * @resources: Pointer to the game_resource_t struct representing
 * the game resources.
 * @event: Pointer to SDL_Event struct
 */
void handle_sdl_keydown(game_resources_t *resources, SDL_Event *event)
{

	/* Generated when a key is pressed*/
	if (event->key.keysym.sym == SDLK_ESCAPE)
		resources->context.game_is_running = false;

	/* Check for opposite keys pressed simultaneously */
	if (((event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_w)
	     && (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN] ||
		 SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])) ||
	    ((event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym ==
	      SDLK_s) && (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] ||
			  SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])))
	{
		resources->player.walk_direction = 0; /* Don't move */
	}
	else if (((event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym ==
		   SDLK_a) && (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]
			       || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]))
		 || ((event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym
		      == SDLK_d) && (SDL_GetKeyboardState(NULL)
				     [SDL_SCANCODE_LEFT] || SDL_GetKeyboardState
				     (NULL)[SDL_SCANCODE_A])))
	{
		resources->player.walk_direction = 0;
		resources->player.turn_direction = 0; /* Don't move */
	}
	else
	{
		process_other_movement_keys(resources, event);
	}
}
/**
 * process_other_movement_keys - processes other movement keys.
 * @resource: Pointer to the game_resource_t struct representing
 * the game resources.
 * @e: Pointer to SDL_Event struct.
 */
void process_other_movement_keys(game_resources_t *resource, SDL_Event *e)
{
	if ((e->key.keysym.sym == SDLK_UP || e->key.keysym.sym == SDLK_w)
	    && (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] ||
		SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]))
	{
		resource->player.walk_direction += 1;
		resource->player.turn_direction += 1;
	}
	else if ((e->key.keysym.sym == SDLK_UP || e->key.keysym.sym == SDLK_w)
			&& (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] ||
				SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]))
	{
		resource->player.walk_direction += 1;
		resource->player.turn_direction -= 1;
	}
	else if ((e->key.keysym.sym == SDLK_DOWN || e->key.keysym.sym == SDLK_s)
		 && (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] ||
		     SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]))
	{
		resource->player.walk_direction -= 1;
		resource->player.turn_direction = +1;
	}
	else if ((e->key.keysym.sym == SDLK_DOWN || e->key.keysym.sym == SDLK_s)
		 && (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] ||
		     SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]))
	{
		resource->player.walk_direction -= 1;
		resource->player.turn_direction -= 1;
	}
	else if (e->key.keysym.sym == SDLK_UP || e->key.keysym.sym == SDLK_w)
		resource->player.walk_direction += 1;
	else if (e->key.keysym.sym == SDLK_DOWN || e->key.keysym.sym == SDLK_s)
		resource->player.walk_direction -= 1;
	else if (e->key.keysym.sym == SDLK_RIGHT || e->key.keysym.sym == SDLK_d)
		resource->player.turn_direction = +1; /* Turn reight */
	else if (e->key.keysym.sym == SDLK_LEFT || e->key.keysym.sym == SDLK_a)
		resource->player.turn_direction -= 1; /* Turn left */
}

/**
 * handle_sdl_keyup - Handles a key when released.
 * @resources: Pointer to the game_resource_t struct representing
 * the game resources.
 * @event: Pointer to SDL_Event struct.
 */
void handle_sdl_keyup(game_resources_t *resources, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN ||
			event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_s)
		resources->player.walk_direction = 0;
	if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_LEFT
			|| event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_a)
		resources->player.turn_direction = 0;
}
