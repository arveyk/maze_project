#include <SDL2/SDL.h>
#include "../headers/_demo.h_"
#include <stdio.h>

/**
 * init_instance - initializes stuff
 *
 * @instance: instance to interact with ?
 * Return: 0 on success, 1 on fail
 */
int init_instance(SDL_Instance *instance, int screenW, int screenH,
	int start, char msg[])
{
	msg = "SDL2 \\o/";
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* Create a new Window instance */
	instance->window = SDL_CreateWindow(msg, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1260, 720, SDL_WINDOW_SHOWN);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* Create a new Renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}
