#include <stdio.h>
#include <SDL2/SDL.h>
#include "../headers/_demo.h_"

/**
 * cls - closes the application
 * @texture: texture used in rendering
 * @renderer: image renderer
 * @window: the window on which images are rendered
 *
 * Return: no return value
 */
void cls(SDL_Renderer renderer, SDL_Window window)
{
	/* Free loaded image
	if (texture != NULL)
		SDL_DestroyTexture(texture);
	texture = NULL;
	*/

	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	
	if (window != NULL)
		SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	/* Quit SDL subsystems 
	IMG_Quit();
	*/
	SDL_Quit();
}
