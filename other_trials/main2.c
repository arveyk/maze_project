#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../headers/_demo.h_"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


/**
 * init - initializes screen
 * Return: true on success
 */
int init(SDL_Instance *instance)
{
	int success = 0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n",
				SDL_GetError());
		success = 1;
	}
	else
	{
		/* Create window */
		instance->window = SDL_CreateWindow("SDL Tutorial",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (instance->window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Quit();
			success = 1;
		}
		else
		{
			/* Get window surface*/
			instance->renderer = 
				SDL_CreateRenderer(instance->window, -1, 
						SDL_RENDERER_ACCELERATED | 
					SDL_RENDERER_PRESENTVSYNC);
			if (instance->renderer == NULL)
			{
				SDL_DestroyWindow(instance->window);
				fprintf(stderr, "SDL_CreateRenderer Error: %s\n"
						, SDL_GetError());
				SDL_Quit();
				success = 1;
			}
		}
	}
	return (success);
}

/**
 * poll_events
 *
 * Return: 0 success, 1 fail
 *
 */
int poll_events()
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				/* if 'ESCAPE' is pressed */
				if (key.keysym.scancode == 0x29)
					return (1);
				break;
		}
	}
	return (0);

}
/**
 * close - initializes screen
 * Return: No return value
 
void close(void)
{
	Deallocate surface *
	SDL_FreeSurface(HelloWorld);
	gHelloWorld = NULL;

	*Destroy window *
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	* Quit SDL subsystems *
	SDL_Quit();
}*/

void draw_stuff(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, 10 ,10, 100, 100);
}

/**
 * main - starting point
 * Return: 0 on success
 */
int main(void)
{
	SDL_Instance instance;

	if (init(&instance) != 0)
	{
		printf("Failed to initialize!\n");
		return (1);
	}
	
	
	while ("C is cool")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		/*if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = true;
				}
			}
		}
		*/
		if (poll_events() == 1)
			break;

		draw_stuff(instance);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
