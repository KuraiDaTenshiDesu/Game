#include <stdio.h>
#include "raylib.h"

#include "map.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    InitAudioDevice();
    SetMasterVolume(0.1f);

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    Texture2D PlayerTextureRight = LoadTexture("img/player_right.png");
    Texture2D PlayerTextureLeft = LoadTexture("img/player_left.png");
    Texture2D current = PlayerTextureRight;

    Vector2 playerPosition = (Vector2){(float)100, (float)100};

    Music bgm = LoadMusicStream("sound/bgm_template.mp3");
    PlayMusicStream(bgm);

    bool exitWindowRequested = false;
    bool exitWindow = false;

    SetTargetFPS(60);

    Map_Prepare(50, 50);
    Map_Fill();

    float speed = 10.0f;

    while (!exitWindow)
    {
        UpdateMusicStream(bgm);

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            if (playerPosition.x + speed < width - 100)
            {
                playerPosition.x += speed;
                current = PlayerTextureRight;
            }
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            if (playerPosition.x - speed > 0)
            {
                playerPosition.x -= speed;
                current = PlayerTextureLeft;
            }
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            if (playerPosition.y - speed > 0)
            {
                playerPosition.y -= speed;
            }
        }

        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            if (playerPosition.y + speed < height - 100)
            {
                playerPosition.y += speed;
            }
        }

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            exitWindowRequested = true;
        }

        if (IsKeyPressed(KEY_F))
        {
            ToggleFullscreen();
        }

        if (exitWindowRequested)
        {
            if (IsKeyPressed(KEY_Y))
            {
                exitWindow = true;
            }

            else if (IsKeyPressed(KEY_N))
            {
                exitWindowRequested = false;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        Map_Draw(50);

        DrawTextureEx(current, playerPosition, 0, 0.125, WHITE);

        DrawFPS(50, 50);

        if (exitWindowRequested)
        {
            DrawRectangle(0, 0, width, height + 10, BLACK);
            DrawText("Quit the game? [Y/N]", (float)width / 3, (float)height / 3, 30, WHITE);
        }

        EndDrawing();
    }

    UnloadMusicStream(bgm);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
