#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

const int tileSizeDefault = 16;
const int tilesCols = 16;
const int tilesRows = 12;
const int multiplyer = 4;
const int maxMapSize = 64;
char *map;

const int tileSize = tileSizeDefault * multiplyer;

struct Tile
{
	Texture2D texture;
	bool walkable;
};

struct Tile tiles[10];

void Map_Init()
{
    tiles[0] = (struct Tile){LoadTexture("resources/img/grass.png"), true};
	tiles[1] = (struct Tile){LoadTexture("resources/img/stone_wall.png"), false};
	tiles[2] = (struct Tile){LoadTexture("resources/img/stone_road.png"), true};
	tiles[3] = (struct Tile){LoadTexture("resources/img/dirt.png"), true};
	tiles[4] = (struct Tile){LoadTexture("resources/img/planks.png"), true};
	tiles[5] = (struct Tile){LoadTexture("resources/img/birch_on_grass.png"), false};
	tiles[6] = (struct Tile){LoadTexture("resources/img/oak_on_grass.png"), false};

    map = LoadFileText("resources/maps/bigMap1.txt");
}

bool Check_Collision(char * map, Vector2 coordinates)
{

	return tiles[(int)map[((int)(coordinates.y + 32)/ 64 * maxMapSize) + ((int)(coordinates.x + 32) / 64)] - (int)'0'].walkable;
}

void Draw_Tiles(char *map)
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < strlen(map); i++)
	{

		if ((int)map[i] != 10)
		{
			DrawTexturePro(tiles[(int)map[i] - (int)'0'].texture,
						   (Rectangle){0, 0, tileSizeDefault, tileSizeDefault},
						   (Rectangle){x * tileSize, y * tileSize, tileSize, tileSize},
						   (Vector2){0, 0}, 0, WHITE);

			x++;
			if (x == maxMapSize)
			{
				x = 0;
				y++;
			}
		}
	}
}
