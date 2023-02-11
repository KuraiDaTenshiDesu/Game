#include <stdio.h>
#include "raylib.h"

#include "map.h"

int main(void)
{
    // Window
    const int screenWidthDefault = 800;
    const int screenHeightDefault = 600;

    InitWindow(screenWidthDefault, screenHeightDefault, "raylib [core] example - keyboard input");
    const int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());
    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen();

    SetTargetFPS(60);

    bool exitWindowRequested = false;
    bool exitWindow = false;

    // Audio
    InitAudioDevice();
    SetMasterVolume(0.2f);
    Music bgm = LoadMusicStream("sound/bgm_template.mp3");
    PlayMusicStream(bgm);

    // Player
    Texture2D PlayerTextureRight = LoadTexture("img/player_right.png");
    Texture2D PlayerTextureLeft = LoadTexture("img/player_left.png");
    Texture2D PlayerTextureFront = LoadTexture("img/player_front.png");
    Texture2D PlayerTextureBack = LoadTexture("img/player_back.png");

    Texture2D currentPlayerTexture = PlayerTextureFront;

    Vector2 playerPosition = (Vector2){(float)screenWidth / 2 - 64, (float)screenWidth / 2 - 64};
    float speed = 10.0f;

    // Map
    Map_Prepare(50, 50);
    Map_Fill();

    while (!exitWindow)
    {
        UpdateMusicStream(bgm);

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            currentPlayerTexture = PlayerTextureRight;
            if (playerPosition.x + speed < screenWidth - 128)
            {
                playerPosition.x += speed;
            }
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            currentPlayerTexture = PlayerTextureLeft;
            if (playerPosition.x - speed > 0)
            {
                playerPosition.x -= speed;
            }
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            currentPlayerTexture = PlayerTextureBack;
            if (playerPosition.y - speed > 160)
            {
                playerPosition.y -= speed;
            }
        }

        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            currentPlayerTexture = PlayerTextureFront;
            if (playerPosition.y + speed < screenHeight - 128)
            {
                playerPosition.y += speed;
            }
        }

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            exitWindowRequested = true;
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

        DrawTextureEx(currentPlayerTexture, playerPosition, 0, 1, WHITE);

        DrawFPS(50, 50);

        if (exitWindowRequested)
        {
            DrawRectangle(0, 0, screenWidth, screenHeight + 10, BLACK);
            DrawText("Quit the game? [Y/N]", (float)screenWidth / 3, (float)screenHeight / 3, 30, WHITE);
        }

        EndDrawing();
    }

    UnloadMusicStream(bgm);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
