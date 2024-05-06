#include <SDL2/SDL.h>
#include "_demo.h_"
#include <math.h>

int poll_events(void);
void draw_stuff(SDL_Instance instance);
int init_instance(SDL_Instance *instance);

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 640
#define screenHeight 480

int worldMap[24][24] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/**
 * main - starting point
 *
 * Return: 0 (Success)
 */
int main(void)
{
	double posX = 22, posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66; /* 2d raycaster version of camera plane*/
	double time = 0;
	double oldTime = 0;
	
	int mapX;
	int mapY;

	/* length f ray from one x or y-side to the next x or y-side */
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	double cameraX; 
	double rayDirX;
	double rayDirY;
	double moveSpeed, rotSpeed;
	double frameTime;
	double oldPlaneX, oldDirX;
	double rayDirX, rayDiry, w;


	/* Direction to step in x or y (either +1 or -1) */
	int stepX;
	int stepY;
	int xorcolor; 
	int ycolor;
	int xycolor;
	int lineHeight;
	int drawStart, drawEnd;

	int hit = 0; /* Was there a wall hit? */
	int side; /* was a NS or a EW wall hit*/
	int i;
	 

	/* SDL_Instance instance; */
	ColorRGB color;
	Screen(screenWidth, screenHeight, 0, "Raycaster");

	/* if (init_instance(&instance) != 0)
		return (1);
		*/

	for (i = 0; i < 8; i++)
		texture[i].resize(texWidth * texHeight);
	for (x = 0; x < texWidth; x++)
	{
		for (y = 0; y < texHeight; y++)
		{
			xorcolour = (x * 256 / texWidth) ^ (y * 256 / texHeight); 
			ycolor = y * 256 / texHeight;
			xycolor = y * 128 / texHeight + x * 128 / texWidth;
			
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); 
			/* flat red texture with black cross */
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; /* sloped greyscale */
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; /* sloped yellow gradient */
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; /* xor greyscale */
			texture[4][texWidth * y + x] = 256 * xorcolor; /* xor green */
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); /* red bricks */
			texture[6][texWidth * y + x] = 65536 * ycolor;
			/* red gradient */
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
			/* flat grey texture */
		}
	}

	while ("C is awesome")
	{
		for (x = 0; x < w; x++)
		{
			cameraX = 2 * x/w - 1;
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;
			
			/* which box of the map we are in*/
			mapX = (int)posX;
			mapY = (int)posY;
			
			deltaDistX = sqrt(1 + (rayDirY * 
						rayDirY) / (rayDirX * rayDirX));
			deltaDistY = sqrt(1 + (rayDirX * 
						rayDirX) / (rayDirY * rayDirY));
			hit = 0; /* Was there a wall hit? */

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

		}
		/* perform DDA */
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
				hit  = 1;
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		/* Height of line to draw on screen */
		lineHeight = (int)(h / perpWallDist);

		/* Calc lowest and highest pixel to fill in current stripe */
		drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;
		switch(worldMap[mapX][mapY])
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
			default :
				color = RGB_Yellow;
				break;
		}
		if (side == 1) /* give x and y sides different brighness*/
			color = color / 2;
		/* draw the pixels of the stripe as vertical line */
		verLine(x, drawStart, drawEnd, color);
		oldTime = time;
		time = getTicks();
	       	/* time this frame has taken in seconds*/
		frameTime = (time -oldTime) / 1000.0;
		printf(1.0 /frameTime);
		redraw();
		cls();
		moveSpeed = frameTime * 5.0;
		rotSpeed = frameTime * 3.0;

		readKeys();
		/* move forward if no wall in front of you */
		if (keyDown(SDLK_UP))
		{
			if(worldMap[int(posX + dirX * moveSpeed)]
					[int(posY)] == false) posX += dirX * moveSpeed;
			if(worldMap[int(posX)][int(posY + dirY * moveSpeed)]
				       	== false) posY += dirY * moveSpeed;
		}
		/* move backwards if no wall behind you */
		if (keyDown(SDLK_DOWN))
		{
			if(worldMap[int(posX - dirX * moveSpeed)][int(posY)]
				       	== false) posX -= dirX * moveSpeed;
			if(worldMap[int(posX)][int(posY - dirY * moveSpeed)]
				       	== false) posY -= dirY * moveSpeed;
		}
		/* rotate to the right */
		if (keyDown(SDLK_RIGHT))
		{
			/* both camera direction and camera plane must be rotated*/
			oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		/* rotate to the left */
		if (keyDown(SDLK_LEFT))
		{
			/* both camera direction and camera plane must be rotated*/
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}

		/*
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		 * Draw some stuff here
		if (poll_events() == 1)
			break;
		draw_stuff(instance);
		SDL_RenderPresent(instance.renderer);
		 */
	}
		 /*
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
		 */
	return (0);

}

/**
 * init_instance - initializes stuff
 *
 * @instance: instance to interact with ?
 * Return: 0 on success, 1 on fail
 */
int init_instance(SDL_Instance *instance)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* Create a new Window instance */
	instance->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1260, 720, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Create a new Renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
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
