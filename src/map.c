#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#include "pair.h"

struct
{
    Pair pair;
    int *matrix;
} Map;

Texture2D wood;
Texture2D stone;
int tileSize = 64;

void Map_Prepare(int x, int y)
{
    wood = LoadTexture("img/wood.png");
    stone = LoadTexture("img/stone.png");
    Map.pair.x = x;
    Map.pair.y = y;
    Map.matrix = (int *)malloc(sizeof(int) * x * y);
}

void Map_Fill()
{
    srand(time(NULL));

    for (int x = Map.pair.x - 1; x >= 0; x--)
    {
        for (int y = Map.pair.y - 1; y >= 0; y--)
        {
            if (y >= 3)
            {
                Map.matrix[x * Map.pair.x + y] = 2;
            }

            if (y < 3)
            {
                Map.matrix[x * Map.pair.x + y] = 1;
            }
        }
    }
}

Texture2D current;
void Map_Draw()
{
    for (int x = Map.pair.x - 1; x >= 0; x--)
    {
        for (int y = Map.pair.y - 1; y >= 0; y--)
        {
            if (Map.matrix[x * Map.pair.x + y] == 1)
            {
                current = stone;
            }

            if (Map.matrix[x * Map.pair.x + y] == 2)
            {
                current = wood;
            }

            DrawTexture(current, x * tileSize, y * tileSize, WHITE);
        }
    }
}