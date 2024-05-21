#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../headers/maze.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


bool loadMedia(SDL_Surface* HelloWorld);
bool init(SDL_Window *Window);
void cls(SDL_Window *Window, SDL_Surface *ScreenSurface);

/**
 * init - initializes screen
 * Return: true on success
 */
bool init(SDL_Window *Window)
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
		Window = SDL_CreateWindow("SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
	}
	return (success);
}

/**
 * loadMedia - initializes screen
 * Return: true on success
 */
bool loadMedia(SDL_Surface* HelloWorld)
{
	/* Loading success flag */
	bool success = true;

	/* Load splash image */
	HelloWorld = SDL_LoadBMP("../images/hello_world.bmp");
	if (HelloWorld == NULL)
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
void cls(SDL_Window *Window, SDL_Surface *HelloWorld)
{
	/*Deallocate surface */
	if (HelloWorld != NULL)
		SDL_FreeSurface(HelloWorld);
	HelloWorld = NULL;

	/*Destroy window */
	if (Window != NULL)
		SDL_DestroyWindow(Window);
	Window = NULL;

	/* Quit SDL subsystems */
	SDL_Quit();
}

/**
 * main - starting point
 * Return: 0 on success
 */
int main(void)
{
	SDL_Window *Window = NULL;
	SDL_Surface *ScreenSurface = NULL;
	SDL_Surface *HelloWorld = NULL;
	bool quit = false;
	SDL_Event e;

	if (!init(Window))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		/* Get window surface*/
		ScreenSurface = SDL_GetWindowSurface(Window);
		if (!loadMedia(HelloWorld))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			SDL_BlitSurface(HelloWorld, NULL, ScreenSurface, NULL);
			SDL_UpdateWindowSurface(Window);
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
	cls(Window, HelloWorld);
	return (0);
}
