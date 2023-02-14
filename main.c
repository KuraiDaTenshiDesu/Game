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
int framesDelay = 10;
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
	Texture2D textures[4];
	int currentTexture;
} Player;

enum
{
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

void Player_Init(Vector2 coordinates, float speed, Image front, Image back, Image left, Image right)
{
	Player.coordinates.x = coordinates.x;
	Player.coordinates.y = coordinates.y;
	Player.speed = speed;

	Player.textures[0] = LoadTextureFromImage(front);
	Player.textures[1] = LoadTextureFromImage(back);
	Player.textures[2] = LoadTextureFromImage(left);
	Player.textures[3] = LoadTextureFromImage(right);

	Player.currentTexture = FRONT;
}

void Player_Move(Image texture)
{
	if (IsKeyDown(KEY_W))
	{
		Player.coordinates.y -= Player.speed;
		Player.currentTexture = BACK;
		Update_Frame(texture, Player.textures[Player.currentTexture]);
	}

	if (IsKeyDown(KEY_S))
	{
		Player.coordinates.y += Player.speed;
		Player.currentTexture = FRONT;
		Update_Frame(texture, Player.textures[Player.currentTexture]);
	}

	if (IsKeyDown(KEY_A))
	{
		Player.coordinates.x -= Player.speed;
		Player.currentTexture = LEFT;
		Update_Frame(texture, Player.textures[Player.currentTexture]);
	}

	if (IsKeyDown(KEY_D))
	{
		Player.coordinates.x += Player.speed;
		Player.currentTexture = RIGHT;
		Update_Frame(texture, Player.textures[Player.currentTexture]);
	}

	if (IsKeyPressed(KEY_LEFT_SHIFT))
	{
		Player.speed += 5.0f;
	}

	if (IsKeyReleased(KEY_LEFT_SHIFT))
	{
		Player.speed -= 5.0f;
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
	Image textureAnims[4];
	textureAnims[0] = LoadImageAnim("resources/img/player_front.gif", &frames);
	textureAnims[1] = LoadImageAnim("resources/img/player_back.gif", &frames);
	textureAnims[2] = LoadImageAnim("resources/img/player_left.gif", &frames);
	textureAnims[3] = LoadImageAnim("resources/img/player_right.gif", &frames);

	Player_Init((Vector2){100, 100}, 2.5f, textureAnims[0], textureAnims[1], textureAnims[2], textureAnims[3]);

	// Map tiles
	struct Tile grass = (struct Tile){LoadTexture("resources/img/grass.png"), true};

	// Game loop
	while (!WindowShouldClose())
	{
		Player_Move(textureAnims[Player.currentTexture]);

		// Drawing
		BeginDrawing();

		ClearBackground(WHITE);

		Draw_Tiles(grass);

		DrawTextureEx(Player.textures[Player.currentTexture], Player.coordinates, 0, multiplyer, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}