#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

// Main info
const int tileSizeDefault = 16;
const int tilesCols = 16;
const int tilesRows = 12;
const int multiplyer = 4;

const int tileSize = tileSizeDefault * multiplyer;

const int FrameRate = 60;
int frames = 0;
int currentFrame = 0;
int framesDelay = 5;
int frameCounter = 0;
unsigned int nextFrameDataOffset = 0;

void Update_Frame(Image image, Texture2D texture)
{
	frameCounter++;
	if (frameCounter == framesDelay)
	{
		currentFrame++;
		if (currentFrame >= frames)
		{
			currentFrame = 0;
		}

		frameCounter = 0;
	}

	nextFrameDataOffset = image.width * image.height * 4 * currentFrame;
	UpdateTexture(texture, ((unsigned char *)image.data) + nextFrameDataOffset);
}

// Player
struct
{
	Vector2 coordinates;
	float speed;
	Texture2D textures[2];
	int currentDirection;
} Player;

enum
{
	LEFT,
	RIGHT
};

void Player_Init(Vector2 coordinates, float speed, Image left, Image right)
{
	Player.coordinates.x = coordinates.x;
	Player.coordinates.y = coordinates.y;
	Player.speed = speed;

	Player.textures[0] = LoadTextureFromImage(left);
	Player.textures[1] = LoadTextureFromImage(right);

	Player.currentDirection = RIGHT;
}

void Player_Move(Image texture)
{
	if (IsKeyDown(KEY_W))
	{
		Player.coordinates.y -= Player.speed;
		Update_Frame(texture, Player.textures[Player.currentDirection]);
	}

	if (IsKeyDown(KEY_S))
	{
		Player.coordinates.y += Player.speed;
		Update_Frame(texture, Player.textures[Player.currentDirection]);
	}

	if (IsKeyDown(KEY_A))
	{
		Player.coordinates.x -= Player.speed;
		Player.currentDirection = LEFT;
		Update_Frame(texture, Player.textures[Player.currentDirection]);
	}

	if (IsKeyDown(KEY_D))
	{
		Player.coordinates.x += Player.speed;
		Player.currentDirection = RIGHT;
		Update_Frame(texture, Player.textures[Player.currentDirection]);
	}

	if (IsKeyPressed(KEY_LEFT_SHIFT))
	{
		Player.speed += 3.0f;
	}

	if (IsKeyReleased(KEY_LEFT_SHIFT))
	{
		Player.speed -= 3.0f;
	}
}

// Tiles
struct Tile
{
	Texture2D texture;
	bool walkable;
};

struct Tile tiles[10];

void Draw_Tiles()
{
	for (int x = 0; x < tilesCols; x++)
	{
		for (int y = 0; y < tilesRows; y++)
		{
			if (x == 0 || y == 0 || x == tilesCols - 1 || y == tilesRows - 1)
			{
				DrawTextureEx(tiles[1].texture, (Vector2){x * tileSize, y * tileSize}, 0, multiplyer, WHITE);
			}
			else
			{
				DrawTextureEx(tiles[0].texture, (Vector2){x * tileSize, y * tileSize}, 0, multiplyer, WHITE);
			}
		}
	}
}

void Draw_Tiles_Test(char *map)
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
	Image textureAnims[2];
	textureAnims[0] = LoadImageAnim("resources/img/player_left.gif", &frames);
	textureAnims[1] = LoadImageAnim("resources/img/player_right.gif", &frames);

	Player_Init((Vector2){100, 100}, 2.0f, textureAnims[0], textureAnims[1]);

	// Map tiles
	tiles[0] = (struct Tile){LoadTexture("resources/img/grass.png"), true};
	tiles[1] = (struct Tile){LoadTexture("resources/img/stone_wall.png"), false};

	// printf("%lld \n", strlen(LoadFileText("resources/maps/map.txt")));

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
	}

	// ========================
	// GAME LOOP
	//=========================
	while (!WindowShouldClose())
	{
		Player_Move(textureAnims[Player.currentDirection]);

		// Drawing
		BeginDrawing();

		ClearBackground(WHITE);

		Draw_Tiles_Test(map);

		DrawTextureEx(Player.textures[Player.currentDirection], Player.coordinates, 0, multiplyer, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}