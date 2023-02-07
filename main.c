#include <stdio.h>
#include "raylib.h"

#include "map.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Map_Prepare(10, 10);
    Map_Fill();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Game Would Be Here", screenWidth / 2, screenHeight / 2, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}