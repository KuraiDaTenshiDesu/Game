#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
// #include "textures_draw_tiled.c"

// Main info

const int tileSizeDefault = 16;
const int tilesCols = 16;
const int tilesRows = 12;
const int multiplyer = 4;

const int tileSize = tileSizeDefault * multiplyer;

const int FrameRate = 60;

int frames = 0;
int currentFrame = 0;
int framesDelay = 10;
int frameCounter = 0;
unsigned int nextFrameDataOffset = 0;
int maxAtlasFrames = 1;
int atlasX = 0;
int atlasY = 0;

// Player
struct
{
	Vector2 coordinates;
	float speed;
	Texture2D textureAtlas;
	int currentDirection;
} Player;

enum
{
	LEFT,
	RIGHT
};

void Player_Init(Vector2 coordinates, float speed, Texture2D atlas)
{
	Player.coordinates.x = coordinates.x;
	Player.coordinates.y = coordinates.y;
	Player.speed = speed;

	Player.textureAtlas = atlas;

	Player.currentDirection = RIGHT;
}

void Player_Move()
{
	if (IsKeyDown(KEY_W))
	{
		Player.coordinates.y -= Player.speed;
	}

	if (IsKeyDown(KEY_S))
	{
		Player.coordinates.y += Player.speed;
	}

	if (IsKeyDown(KEY_A))
	{
		Player.coordinates.x -= Player.speed;
		Player.currentDirection = LEFT;
	}

	if (IsKeyDown(KEY_D))
	{
		Player.coordinates.x += Player.speed;
		Player.currentDirection = RIGHT;
	}

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
	{
		frameCounter++;
		atlasY = Player.currentDirection;

		if (frameCounter == framesDelay)
		{
			frameCounter = 0;
			atlasX++;

			if (atlasX > maxAtlasFrames)
			{
				atlasX = 0;
			}
		}
	}
}

// Tiles
struct Tile
{
	Texture2D texture;
	bool walkable;
};

struct Tile tiles[10];

void Draw_Tiles(char *map)
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < strlen(map); i++)
	{
		if ((int)map[i] != 10)
		{
			DrawTextureEx(tiles[(int)map[i] - (int)'0'].texture, (Vector2){x * tileSize, y * tileSize}, 0, multiplyer, WHITE);

			x++;
			if (x == tilesCols)
			{
				x = 0;
				y++;
			}
		}
	}
}

// ========================
// MAIN
//=========================

int main(void)
{
	// Window
	const int screenWidth = tileSize * tilesCols;
	const int screenHeight = tileSize * tilesRows;

	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(FrameRate);

	// Player

	Texture2D atlas = LoadTexture("resources/img/player_atlas.png");

	Player_Init((Vector2){100, 100}, 2.0f, atlas);

	// Map tiles
	tiles[0] = (struct Tile){LoadTexture("resources/img/grass.png"), true};
	tiles[1] = (struct Tile){LoadTexture("resources/img/stone_wall.png"), false};

	int mapNum = GetRandomValue(1, 3);
	char *map;

	switch (mapNum)
	{
	case 1:
		map = LoadFileText("resources/maps/map1.txt");
		break;
	case 2:
		map = LoadFileText("resources/maps/map2.txt");
		break;
	case 3:
		map = LoadFileText("resources/maps/map3.txt");
		break;
	default:
		map = LoadFileText("resources/maps/map1.txt");
	}

	// ========================
	// GAME LOOP
	//=========================
	while (!WindowShouldClose())
	{
		Player_Move();

		// Drawing
		BeginDrawing();

		ClearBackground(WHITE);

		Draw_Tiles(map);

		// DrawTextureEx(Player.textures[Player.currentDirection], Player.coordinates, 0, multiplyer, WHITE);
		DrawTexturePro(Player.textureAtlas,
					   (Rectangle){atlasX * tileSizeDefault, atlasY * tileSizeDefault, tileSizeDefault, tileSizeDefault},
					   (Rectangle){Player.coordinates.x, Player.coordinates.y, tileSize, tileSize},
					   (Vector2){0, 0}, 0, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}