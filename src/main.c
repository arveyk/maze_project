#include <SDL2/SDL.h>
#include "../headers/_demo.h_"

int poll_events(void);
void draw_stuff(SDL_Instance instance);
void cls(SDL_Renderer *renderer, SDL_Window *window);
int init_instance(SDL_Instance *instance, int screenW, int screenH,
		int start, char msg[]);
int load_media(SDL_Surface *hello_image, char *file_path);
/**
 * main - starting point
 *
 * Return: 0 (Success)
 */
int main(void)
{

	SDL_Instance instance;
	SDL_Surface *screenSurface = NULL;
	SDL_Surface* hello_image = NULL;
	int quit = 0;
	int screenW = 600;
	int screenH = 400;

	if (init_instance(&instance, screenW, screenH, 0, start) != 0)
		return (1);

	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		/* Clear screen*/
		SDL_RenderClear(instance.renderer);
		while (quit == 0)
		{
			if (poll_events() == 1)
			break;
		}
		
		screenSurface = SDL_GetWindowSurface(instance.window);
		if (screenSurface == NULL)
		{
			fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
			SDL_Quit();
			return (1);
		}

		/*
		 * Draw some stuff here
		 */
		draw_stuff(instance);
		/*Update Screen*/
		SDL_RenderPresent(instance.renderer);

		if (!load_media(hello_image, "../images/hello_world.bmp"))
			printf("Failed to load media!\n");
		else
		{
			SDL_BlitSurface(hello_image, screenSurface, NULL);
			SDL_UpdateWindowSurface(instance.window);
		}

	}
	
	cls(instance.window, instance.renderer);
	return (0);

}


/**
 * draw_stuff - draws stuff in the screen
 *
 * @instance: instance to draw
 * Return: no return value
 */
void draw_stuff(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, 10, 10, 100, 100);
}
