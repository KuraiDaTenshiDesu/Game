#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "pair.h"

struct
{
    Pair pair;
    int *matrix;
} Map;

Texture2D textures[2];

int tileSize = 64;

void Map_Prepare(int x, int y)
{
    textures[0] = LoadTexture("img/wood.png");
    textures[1] = LoadTexture("img/stone.png");

    Map.pair.x = x;
    Map.pair.y = y;
    Map.matrix = (int *)malloc(sizeof(int) * x * y);
}

void Map_Fill()
{
    for (int x = Map.pair.x - 1; x >= 0; x--)
    {
        for (int y = Map.pair.y - 1; y >= 0; y--)
        {
            if (y >= 3)
            {
                Map.matrix[x * Map.pair.x + y] = 0;
            }

            if (y < 3)
            {
                Map.matrix[x * Map.pair.x + y] = 1;
            }
        }
    }
}

void Map_Draw()
{
    for (int x = Map.pair.x - 1; x >= 0; x--)
    {
        for (int y = Map.pair.y - 1; y >= 0; y--)
        {
            DrawTexture(textures[Map.matrix[x * Map.pair.x + y]], x * tileSize, y * tileSize, WHITE);
        }
    }
}