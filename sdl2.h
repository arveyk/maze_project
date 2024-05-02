#ifndef SDL2_H
#define SDL2_H
#include <SDL2/SDL.h">

typedef struct SDL_Instance 
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance instance);

#endif /* SDL2_H*/
