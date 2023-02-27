#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

// Main info
const int tileSizeDefault = 16;
const int tilesCols = 16;
const int tilesRows = 12;
const int multiplyer = 4;
const int maxMapSize = 64;

const int tileSize = tileSizeDefault * multiplyer;

const int FrameRate = 60;

int framesDelay = 10;
int frameCounter = 0;
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

	Camera2D camera;
	camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	// Player

	Texture2D atlas = LoadTexture("resources/img/player_atlas.png");

	Player_Init((Vector2){tileSize * 2, tileSize * 1}, 2.0f, atlas);

	// Map tiles
	tiles[0] = (struct Tile){LoadTexture("resources/img/grass.png"), true};
	tiles[1] = (struct Tile){LoadTexture("resources/img/stone_wall.png"), false};
	tiles[2] = (struct Tile){LoadTexture("resources/img/stone_road.png"), true};
	tiles[3] = (struct Tile){LoadTexture("resources/img/dirt.png"), true};
	tiles[4] = (struct Tile){LoadTexture("resources/img/planks.png"), true};
	tiles[5] = (struct Tile){LoadTexture("resources/img/birch_on_grass.png"), false};
	tiles[6] = (struct Tile){LoadTexture("resources/img/oak_on_grass.png"), false};

	char *map = LoadFileText("resources/maps/bigMap1.txt");

	// ========================
	// GAME LOOP
	//=========================
	while (!WindowShouldClose())
	{
		camera.target = (Vector2){Player.coordinates.x + tileSize / 2, Player.coordinates.y + tileSize / 2};
		Player_Move();

		// Drawing
		BeginDrawing();
		BeginMode2D(camera);

		ClearBackground(BLACK);

		Draw_Tiles(map);

		DrawTexturePro(Player.textureAtlas,
					   (Rectangle){atlasX * tileSizeDefault, atlasY * tileSizeDefault, tileSizeDefault, tileSizeDefault},
					   (Rectangle){Player.coordinates.x, Player.coordinates.y, tileSize, tileSize},
					   (Vector2){0, 0}, 0, WHITE);

		EndMode2D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}