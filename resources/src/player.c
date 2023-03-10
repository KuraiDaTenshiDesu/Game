#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "map.h"

int framesDelay = 10;
int frameCounter = 0;
int maxAtlasFrames = 1;
int atlasX = 0;
int atlasY = 0;

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

void Player_Move(char * map)
{
	if (IsKeyDown(KEY_W))
	{
		Player.coordinates.y -= Player.speed;

		if (!Check_Collision(map, Player.coordinates))
		{
			Player.coordinates.y += Player.speed;
		}
	}

	if (IsKeyDown(KEY_S))
	{
		Player.coordinates.y += Player.speed;
		
		if (!Check_Collision(map, Player.coordinates))
		{
			Player.coordinates.y -= Player.speed;
		}
	}

	if (IsKeyDown(KEY_A))
	{
		Player.coordinates.x -= Player.speed;
		Player.currentDirection = LEFT;
		
		if (!Check_Collision(map, Player.coordinates))
		{
			Player.coordinates.x += Player.speed;
		}
	}

	if (IsKeyDown(KEY_D))
	{
		Player.coordinates.x += Player.speed;
		Player.currentDirection = RIGHT;
		
		if (!Check_Collision(map, Player.coordinates))
		{
			Player.coordinates.x -= Player.speed;
		}
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

void Player_Draw()
{
	DrawTexturePro(Player.textureAtlas,
		   	      (Rectangle){atlasX * tileSizeDefault, atlasY * tileSizeDefault, tileSizeDefault, tileSizeDefault},
				  (Rectangle){Player.coordinates.x, Player.coordinates.y, tileSize, tileSize},
				  (Vector2){0, 0}, 0, WHITE);
}

Vector2 Player_GetCoordinates()
{
	return (Vector2) {Player.coordinates.x, Player.coordinates.y};
}