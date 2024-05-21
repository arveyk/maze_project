#ifndef MAZE_H
#define MAZE_H
#include <SDL2/SDL.h>

typedef struct SDL_Instance 
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

void cls(SDL_Window *Window, SDL_Surface *ScreenSurface);
void draw_stuff(SDL_Instance instance);
bool init(SDL_Window *Window);
bool loadMedia(SDL_Surface* HelloWorld);

#endif /* MAZE_H*/
