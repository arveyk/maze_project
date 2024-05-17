#include <SDL2/SDL.h>
#include "../headers/_demo.h_"

/**
 * poll_events - prints event
 * Return: 0 (Success)
 */
int poll_events(void)
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
			/* If 'ESCAPE' is pressed */
				if (key.keysym.scancode == 0x29)
					return (1);
				break;
		}
	}
	return (0);
}
