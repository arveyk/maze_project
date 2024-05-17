#include "../headers/_demo.h_"
#include <SDL2/SDL.h>

/**
 * loadTextures  - loads a textures
 * texPath
 *
 * Return: new texture
 */
SDL_Texture *loadTexture(SDL_Renderer *renderer, char texPath[])
{
	/* final texture */
	SDL_Texture *newTexture = NULL;

	/* image at specified path */
	SDL_Surface *loadedSurface = IMG_load(texPath);

	if (loadedsurface = NULL)
		printf("Unable load image %s! SDL_image Error: %d\n",
				texPath, IMG_GetError());
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
			printf("Unable to create texture from %s! SDL_Error: %d\n",
					texPath, SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);

	return (newTexture);
}
