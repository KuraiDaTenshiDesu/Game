#include <stdio.h>
#include "raylib.h"

#include "map.h"

struct
{
    int hp;
    int atk;
    Texture2D textures[4];
    Vector2 position;
    float speed;
} Player;

void Player_Init(int hp, int atk, float x, float y, float speed)
{
    Player.hp = hp;
    Player.atk = atk;
    Player.textures[0] = LoadTexture("img/player_front.png");
    Player.textures[1] = LoadTexture("img/player_back.png");
    Player.textures[2] = LoadTexture("img/player_right.png");
    Player.textures[3] = LoadTexture("img/player_left.png");
    Player.position = (Vector2){x, y};
    Player.speed = speed;
}

void Player_Take_Damage()
{
    Player.hp--;
}

void Player_Heal()
{
    if (Player.hp < 10)
    {
        Player.hp++;
    }
}

int main(void)
{
    // Window
    const int screenWidthDefault = 800;
    const int screenHeightDefault = 600;

    InitWindow(screenWidthDefault, screenHeightDefault, "2D Roguelike Game");
    const int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    const int screenHeight = GetMonitorHeight(GetCurrentMonitor());
    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen();
    HideCursor();

    SetTargetFPS(60);

    bool exitWindowRequested = false;
    bool exitWindow = false;

    // Audio
    InitAudioDevice();
    SetMasterVolume(0.2f);
    Music bgm = LoadMusicStream("sound/bgm_template.mp3");
    PlayMusicStream(bgm);

    // Player
    Player_Init(10, 5, (float)screenWidth / 2 - 128, (float)screenHeight / 2 - 128, 5.0f);
    Texture2D currentPlayerTexture = Player.textures[0];

    // Map
    Map_Prepare(50, 50);
    Map_Fill();

    while (!exitWindow)
    {
        UpdateMusicStream(bgm);

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            currentPlayerTexture = Player.textures[2];
            if (Player.position.x + Player.speed < screenWidth - 128)
            {
                Player.position.x += Player.speed;
            }
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            currentPlayerTexture = Player.textures[3];
            if (Player.position.x - Player.speed > 0)
            {
                Player.position.x -= Player.speed;
            }
        }

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            currentPlayerTexture = Player.textures[1];
            if (Player.position.y - Player.speed > 160)
            {
                Player.position.y -= Player.speed;
            }
        }

        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            currentPlayerTexture = Player.textures[0];
            if (Player.position.y + Player.speed < screenHeight - 128)
            {
                Player.position.y += Player.speed;
            }
        }

        if (IsKeyPressed(KEY_Z))
        {
            Player_Take_Damage();
        }

        if (IsKeyPressed(KEY_X))
        {
            Player_Heal();
        }

        if (Player.hp == 0)
        {
            exitWindowRequested = true;
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

        DrawTexture(currentPlayerTexture, Player.position.x, Player.position.y, WHITE);

        for (int i = 1; i <= Player.hp; i++)
        {
            DrawRectangle(50 * i + 10, 50, 40, 40, RED);
        }

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
