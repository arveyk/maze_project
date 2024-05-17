#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool init(void);
bool loadMedia(void);
void close(void);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

/**
 * init - initializes screen
 * Return: true on success
 */
bool init(void)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n",
				SDL_GetError());
		success = false;
	}
	else
	{
		/* Create window */
		gWindow = SDL_CreateWindow("SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			/* Get window surface*/
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return (success);
}

/**
 * loadMedia - initializes screen
 * Return: true on success
 */
bool loadMedia(void)
{
	/* Loading success flag */
	bool success = true;

	/* Load splash image */
	gHelloWorld = SDL_LoadBMP("hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n",
				"hello_world.bmp", SDL_GetError());
		success = false;
	}

	return (success);
}

/**
 * close - initializes screen
 * Return: No return value
 */
void close(void)
{
	/*Deallocate surface */
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	/*Destroy window */
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	/* Quit SDL subsystems */
	SDL_Quit();
}

/**
 * main - starting point
 * Return: 0 on success
 */
int main(void)
{
	bool quit = false;
	SDL_Event e;

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
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
	}
	close();
	return (0);
}
