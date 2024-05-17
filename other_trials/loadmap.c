#include <SDL2/SDL.h>
#include <stdio.h>
/**
 * loadMap - loads a map
 * @filename: file containing map to be loaded
 *
 * Return: no return value
 */
void loadMap(const char *filename)
{
	char *data, *p;
	int x, y;

	data = readFile(filename);
	p = data;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			scanf(p, "%d", &stage.map[x][y]);
			do {
				p++;
			} while (*p != " " && *p != '\n');
		}
	}
	free(data);
}

