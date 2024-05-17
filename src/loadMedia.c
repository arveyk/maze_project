#include "../headers/_demo.h_"
#include <SDL2/SDL.h>

/**
 * load_media - loads images
 * @file_path: path to file to be loaded
 *
 * Return: 1 on success -1 on failure
 */
int load_media(SDL_Surface *hello_image, char *file_path)
{
	int success = 1;

	hello_image = SDL_LoadBPM(filepath);
	if (hello_image == NULL)
	{
		printf("Unable to load image %s SDL Error: %s\n", file_path, SDL_GetError());
		success = -1;
	}

	return (success);
}
