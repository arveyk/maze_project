#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../headers/_demo.h_"
#include <math.h>

#define SCREEN_WIDTH 640 /* 320 */
#define SCREEN_HEIGHT 480 /* 200 */
#define FOV 60
#define PLAYER_HEIGHT 32 /* change to 24 / 2 */


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
			case SDL_KEYUP:
				key = event.key;
				break;
			case SDLK_LEFT:
				key = event.key;
				break;
			case SDLK_RIGHT:
				key = event.key;
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

void draw_stuff(SDL_Instance instance, coordinates hit_point, int height_projection_slice)
{
	int endpX;
	int endpY;
	coordinates start;

	start.y = 100 - (height_projection_slice / 2);
	start.x = hit_point.x;
	printf("%d, %d\n", start.x, start.y);
	endpY =  start.y + height_projection_slice;
	endpX = start.x;

	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, start.x , start.y, endpX, endpY);
}

/**
 * DDA
 *
 */

coordinates dda_alg(coordinates player_pos)
{
	int player_posX = player_pos.x;
	int player_posY = player_pos.y;
	int player_angle = 45;
	coordinates wall_point;
	coordinates cross_point, cross_p2;

	/*int Xa, Ya;  for Increments */

	/* Check horizontal intersection */
	/*Xa = 64 / tan(player_angle);  Horozontal increments
	Ya = 64;*/

	/* first intersection */
	if (player_angle >= 0 && player_angle <= 180)
		cross_point.y = floor(player_posY / 64) * 64 - 1;  /* facing up */
	else
		cross_point.y = floor(player_posY / 64) * 64 + 64; /* facing down */

	cross_point.x = player_posX + (player_posY - cross_point.y) / tan(player_angle);
	
	/* Check vertical intersection 
	Xa = 64;
	Ya = 64 / tan(player_angle);*/

	if (player_angle < 90 || player_angle > 270)
		cross_p2.x = floor(player_posX) * 64 + 64; /* facing right */
	else
		cross_p2.x = floor(player_posX) * 64 - 1; /* facing left */

	cross_p2.y = player_posY + (player_posX - cross_p2.x) 
		* tan(player_angle);

	/* take least of the crossing point */
	if (cross_point.y > cross_p2.y)
	{
		wall_point.x = cross_p2.x;
		wall_point.y = cross_p2.y;
	}
	else
	{
		wall_point.y = cross_point.y;
		wall_point.x = cross_point.x;
	}

	/*
	 * distance_to_wall = abs(player_posY - wall_pointY)
	 * / cos(player_angle);
	 *
	 * fishbow effect corection 
	 * beta = view_angle - FOV;
	 * correct dist = wall_point x cos(beta);
	 */

	/*
	 * drawing the wall
	 *
	 * height_projection_slice = 64 * 277 / distance_to_wall;
	 *
	 * while (x < 319)
	 * {	
	 * starting point 100 - (height_projection_slice / 2);
	 * end point starting point + height_projection_slice;
	 * draw_stuff(insstance, startPoint, endPoint);
	 *}
	 */
	return (wall_point);
}


/**
 * main - starting point
 * Return: 0 on success
 */
int main(void)
{
	SDL_Instance instance;
	coordinates initial_pos, hit_point;

	int player_angle = 45;

	int distance_to_wall, height_projection_slice;

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

		/*
		 * while loop for drawing all the lines
		 * while (x < screen width)
		 * draw a strip 
		 *
		 * increment by 1
		 */


		initial_pos.x = 12;
		initial_pos.y = 12;
		hit_point = dda_alg(initial_pos);

		distance_to_wall = abs(initial_pos.y - hit_point.y)
			/ cos(player_angle);

		height_projection_slice = 64 * 277 / distance_to_wall;


		draw_stuff(instance, hit_point, height_projection_slice);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
