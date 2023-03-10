#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "map.h"
#include "player.h"
#include "camera.h"

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(60);

	Map_Init();
	Player_Init((Vector2){tileSize * 2, tileSize * 1}, 2.0f, LoadTexture("resources/img/player_atlas.png"));
	Camera_Init(screenWidth, screenHeight);
	

	while (!WindowShouldClose())
	{
		
		Player_Move(map);
		Vector2 playerCoordinates = Player_GetCoordinates();
		
		BeginDrawing();

			BeginMode2D(Camera_GetCamera());
			ClearBackground(BLACK);
			Camera_SetTarget((Vector2){playerCoordinates.x + tileSize / 2, playerCoordinates.y + tileSize / 2});
			Draw_Tiles(map);
			Player_Draw();
			EndMode2D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}