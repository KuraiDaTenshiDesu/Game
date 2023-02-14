#include <stdio.h>
#include <stdlib.h>

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
int framesDelay = 3;
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

void Draw_Tiles(struct Tile tile)
{
	for (int x = 0; x < tilesCols; x++)
	{
		for (int y = 0; y < tilesRows; y++)
		{
			DrawTextureEx(tile.texture, (Vector2){x * tileSize, y * tileSize}, 0, multiplyer, WHITE);
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
	struct Tile grass = (struct Tile){LoadTexture("resources/img/grass.png"), true};

	// Game loop
	while (!WindowShouldClose())
	{
		Player_Move(textureAnims[Player.currentDirection]);

		// Drawing
		BeginDrawing();

		ClearBackground(WHITE);

		Draw_Tiles(grass);

		DrawTextureEx(Player.textures[Player.currentDirection], Player.coordinates, 0, multiplyer, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}