#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAPSIZE 256
#define FOG 20.0
#define FPS 60
#define MOVESPEED 0.0875
#define ANGLESPEED 0.005625

bool init(SDL_Window *gWindow);
bool loadMedia(SDL_Surface *HelloWorld);
void closeM(SDL_Surface *HelloW, SDL_Window *window);

int gtline(char s[], int lim);
double distToWall(double playerX, double playerY, double playerA, int map[MAPSIZE][MAPSIZE]);
void readMap(int map[MAPSIZE][MAPSIZE], double *playerX, double *playerY, double *playerA);

bool init(SDL_Window *gWindow)
{
	bool success = true;

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized! SDL_Error: %s\n",
				SDL_GetError());
		success = false;
	}

	else
	{
		/* create Window */
		gWindow = SDL_CreateWindow("SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
			success = false;
		}
	}
	return (success);
}

bool loadMedia(SDL_Surface *gHelloWorld)
{
	/* Loading success flag*/
	bool success = true;

	/* Load Splash Image */
	gHelloWorld = SDL_LoadBMP("hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n",
				"hello_world.bmp", SDL_GetError());
		success = false;
	}
	return (success);
}

void closeM(SDL_Surface *gHelloWorld, SDL_Window *gWindow)
{
	if (gHelloWorld == NULL)
		return;
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	if (gWindow)
		SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}


int main(void)
{
	/*	SDL_Window *window = NULL;
	*/
	SDL_Window *gWindow = NULL;
/* 	SDL_Surface *gScreenSurface = NULL; */
	SDL_Surface *gHelloWorld = NULL;
	SDL_Surface *screenSurface = NULL;
	SDL_Event e;
	const Uint8 *currentKeyStates;

	double playerX = 3.0;
	double playerY = 3.0;
	double playerA = 0.0;
	double dx = 0.0, dy = 0.0;
	double rayAngle; 
	double distance; 
	bool quit;

	int map[MAPSIZE][MAPSIZE];
	int y, x, color = 0;
	int i, j;
	int rectHeight;

	SDL_Rect wall;
	SDL_Rect floor;
	SDL_Rect ceil;
	Uint32 frameTime;
	Uint32 delayTime;

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
			map[i][j] = 0;
	}
	readMap(map, &playerX, &playerY, &playerA);
	if (!init(gWindow))
		printf("Failed to initialize!\n");
	else
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		screenSurface = SDL_GetWindowSurface(gWindow);
		/* Get window surface */
		/* gScreenSurface = SDL_GetWindowSurface(gWindow);*/

		/*
		 * if (!loadMedia(gHelloWorld))
			printf("Failed to load media!\n");
		else
		{
			* Apply the image*
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			*/
		SDL_UpdateWindowSurface(gWindow);
		quit = false;
		while (quit == false)
		{
			Uint32 framestart = SDL_GetTicks();

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = true;
				if (e.type == SDL_MOUSEMOTION)
					playerA += e.motion.xrel * ANGLESPEED;
			}
			currentKeyStates = SDL_GetKeyboardState(0);
			if (currentKeyStates[SDL_SCANCODE_W])
			{
				dx = cos(playerA) * MOVESPEED;
				dy = sin(playerA) * MOVESPEED;
				if (!map[(int)round(playerX + dx)][(int)round(playerY + dy)])
				{
					playerX += dx;
					playerY += dy;
				}
				else if (!map[(int)round(playerX + dx)][(int)round(playerY)])
					playerX += dx;
				else if (!map[(int)round(playerX)][(int)round(playerY + dy)])
					playerY += dy;

			}
			if (currentKeyStates[SDL_SCANCODE_S])
	{
				dx = cos(playerA) * MOVESPEED;
				dy = sin(playerA) * MOVESPEED;
				if (!map[(int)round(playerX - dx)][(int)round(playerY - dy)])
				{
					playerX += dx;
					playerY += dy;
				}
				else if (!map[(int)round(playerX - dx)][(int)round(playerY)])
					playerX -= dx;
				else if (!map[(int)round(playerX)][(int)round(playerY - dy)])
					playerY -= dy;

			}
			if (currentKeyStates[SDL_SCANCODE_ESCAPE])
				quit = true;
			if (currentKeyStates[SDL_SCANCODE_S])
			{
				dx = cos(playerA - 1.57) * MOVESPEED;
				dy = sin(playerA - 1.57) * MOVESPEED;
				if (!map[(int)round(playerX + dx)][(int)round(playerY + dy)])
				{
					playerX += dx;
					playerY += dy;
				}
				else if (!map[(int)round(playerX - dx)][(int)round(playerY)])
					playerX += dx;
				else if (!map[(int)round(playerX)][(int)round(playerY + dy)])
					playerY += dy;
			}
			if (currentKeyStates[SDL_SCANCODE_D])
			{
				dx = cos(playerA - 1.57) * MOVESPEED;
				dy = sin(playerA - 1.57) * MOVESPEED;
				if (!map[(int)round(playerX + dx)][(int)round(playerY + dy)])
				{
					playerX += dx;
					playerY += dy;
				}
				else if (!map[(int)round(playerX - dx)][(int)round(playerY)])
					playerX += dx;
				else if (!map[(int)round(playerX)][(int)round(playerY + dy)])
					playerY += dy;
			}

			SDL_FillRect(screenSurface, 0,
					SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

			wall.w = 1;
			floor.w = SCREEN_WIDTH;
			floor.x = 0;
			floor.h = 1;
			ceil.w = SCREEN_WIDTH;
			ceil.x = 0;
			ceil.h = 1;

			for (y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
			{
				floor.y = y;
				color = 256.0 * ((float)y / (float)SCREEN_HEIGHT);
				SDL_FillRect(screenSurface, &floor,
						SDL_MapRGB(screenSurface->format, 0x00, color, 0x00));
			}
			for (y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
			{
				ceil.y = y;
				color = 256.0 * ((float)y / (float)SCREEN_HEIGHT);
				SDL_FillRect(screenSurface, &ceil,
						SDL_MapRGB(screenSurface->format, 0x00, 0x00, color));
			}
			for (x = 0; x < SCREEN_WIDTH; x++)
			{
				wall.x = x;
				rayAngle = playerA - 0.7853 + (float)x / (float)SCREEN_WIDTH * 1.5706;
				distance = cos(rayAngle - playerA) * distToWall(playerX, playerY, rayAngle, map);
				color = 256.0 * exp(-distance / FOG);
				rectHeight = (int)(SCREEN_WIDTH / distance);
				wall.y = (int) ((SCREEN_HEIGHT - rectHeight) / 2);
				wall.h = rectHeight;
				SDL_FillRect(screenSurface, &wall,
						SDL_MapRGB(screenSurface->format, color, color, color));
			}
			SDL_UpdateWindowSurface(gWindow);

			frameTime = SDL_GetTicks() - framestart;
			delayTime = 1000 / FPS - frameTime;
			if (delayTime > 17)
				delayTime = 0;
			SDL_Delay(delayTime);
		}
	}

	closeM(gHelloWorld, gWindow);
	return (0);
}

double distToWall(double playerX, double playerY, double playerA, int map[MAPSIZE][MAPSIZE])
{
	const double raystep = 0.025;

	double dx = raystep * cos(playerA);
	double dy = raystep * sin(playerA);
	double distance = 0.0, x, y;

	for (x = playerX, y = playerY; !map[(int)round(x)][(int)round(y)]; x += dx, y += dy)
	{
		distance += raystep;
		if (distance > 100)
			return (10000.0);
	}
	return (distance);
}

void readMap(int map[MAPSIZE][MAPSIZE], double *playerX, double *playerY, double *playerA)
{
	char s[256] = { 0 };
	int i, j;

	for (i = 0; i < MAPSIZE; i++)
		for (j = 0; j < MAPSIZE; j++)
			map[i][j] = 0;
	gtline(s, 256);
	*playerX = atof(s);
	gtline(s, 256);
	*playerY = atof(s);
	gtline(s, 256);
	*playerA = atof(s);

	for (i = 0; gtline(s, 256) > 0; i++)
		for (j = 0; s[j] != '\0'; j++)
		{
			if (s[j] == '#')
				map[j][i] = 1;
			else
				map[j][i] = 0;
		}
}

int gtline(char s[], int lim)
{
	char c;
	int i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return (i);
}
