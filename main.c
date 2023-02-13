#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

struct
{
	Vector2 coordinates;
	float speed;
} Player;

void Player_Init(Vector2 coordinates, float speed)
{
	Player.coordinates.x = coordinates.x;
	Player.coordinates.y = coordinates.y;
	Player.speed = speed;
}

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(60);

	Player_Init((Vector2){100, 100}, 5.0f);

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		{
			Player.coordinates.x -= Player.speed;
		}

		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
		{
			Player.coordinates.x += Player.speed;
		}

		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_RIGHT))
		{
			Player.coordinates.y -= Player.speed;
		}

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_LEFT))
		{
			Player.coordinates.y += Player.speed;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangle(Player.coordinates.y, Player.coordinates.x, 100, 100, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}