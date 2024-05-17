#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include "../headers/_demo.h_"
#include <SDL2/SDL_error.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24


double absReturn(double num);
int init_instance(SDL_Instance *instance, int screenW,
		int screenH, int start, char msg[]);

/**
 * main - the starting point
 *
 * Return: 0 on success
 */
int main(void)
{
	int worldMap[24][24] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	double posX = 22, posY = 12; /* x and y start position*/
	double dirX = -1, dirY = 0; /*initial direction vector*/
	double planeX = 0, planeY = 0.66;
	/*the 2d raycaster version of camera plane */


	double cameraX, rayDirX, rayDirY;
	double sideDistX;
	double sideDistY;

	double deltaDistX, deltaDistY;

	int x, mapX, mapY;
	int h = 400, w = 600;
	double perpWallDist;

	int stepX, stepY;
	int side;
	int hit = 0;
	int lineHeight;
	int drawStart, drawEnd;

/*
 * double time = 0; time of current frame
	double oldTime = 0;  time oif previous frame
	double frameTime;
	double moveSpeed, rotSpeed;
	double oldDirX, oldPlaneX;
	*/

	int ret_val = 0;

	ColorRGB color;
	SDL_Instance instance;

	ret_val = init_instance(&instance, screenWidth,
			screenHeight, 0, "Raycaster");
	if (ret_val != 0)
	return (1);

	while ("C is fun")
	{
		SDL_SetRendererDrawColor(instance.renderer, 0, 0, 0, 0);

		for (x = 0; x < w; x++)
		{
			cameraX = 2 * x / w - 1;
			rayDirX = dirX + planeX * cameraX;

			rayDirY = dirY + planeY * cameraX;

			mapX = (int)(posX);
			mapY = (int)(posY);

			deltaDistX = (rayDirX == 0) ? 1e30 : absReturn(1 / rayDirX);
			deltaDistY = (rayDirY == 0) ? 1e30 : absReturn(1 / rayDirY);

			hit = 0;
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);

			lineHeight = (int)(h / perpWallDist);

			drawStart = -lineHeight / 2 + h / 2;

			if (drawStart < 0)
				drawStart = 0;

			drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;

			switch (worldMap[mapX][mapY])
			{
				case 1:
					color = RGB_Red;
					break;
				case 2:
					color = RGB_Green;
					break;
				case 3:
					color = RGB_Blue;
					break;
				case 4:
					color = RGB_White;
					break;
				default:
					color = RGB_Yellow;
					break;
			}

			if (side == 1)
			{
				color = color / 2;
			}
			verLine(x, drawStart, drawEnd, color);
	/*
	 * oldTime = time;
		time = getTicks();
		frameTime = (time - oldTime) / 1000.0;
		print(1.0 / frameTime);
		redraw();
		cls();

		moveSpeed = frameTime * 5.0;
		rotSpeed = frameTime * 3.0;
		readKeys();
		if (keyDown(SDLK_UP))
		{
			if (worldMap[(int)(posX + dirX * moveSpeed)]
					[(int)(posY)] == false)
				posX += dirX * moveSpeed;
			if (worldMap[(int)(posX)][(int)
					(posY + dirY * moveSpeed)] == false)
				posY += dirY * moveSpeed;
		}
		if (keyDown(SDLK_DOWN))
		{
			if (worldMap[(int)(posX - dirX * moveSpeed)]
					[(int)(posY)] == false)
				posX -= dirX * moveSpeed;
			if (worldMap[(int)(posX)][(int)(posY - dirY *
						moveSpeed)] == false)
				posY -= dirY * moveSpeed;
		}
		if (keyDown(SDLK_RIGHT))
		{
			oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		if (keyDown(SDLK_LEFT))
		{

			oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) -
				planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) +
			planeY * cos(rotSpeed);
				}
		*/
		}
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
/**
 * init_instance - initializes a window and renderer to be used in displaying
 * @instance: pointer to the instance to be initialize
 * @screenW: width of the screen/ window to be opened
 * @screenH: height of the screen/window to be opened
 * @start: the players start position(? i think)
 * @msg: massage to print on the dashboard
 *
 * Return: 0 on success, 1 on failure
 */
int init_instance(SDL_Instance *instance, int screenW,
		int screenH, int start, char msg[])
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n",
				SDL_GetError());
		return (1);
	}
	instance->window = SDL_CreateWindow(msg, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, screenW, screenH, start);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error:%s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error:%s\n",
				SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);

}

/**
 * absReturn - returns the absolute value of a given number
 * @num: the number to be evaluated
 *
 * Return: check the function description
 */
double absReturn(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}
