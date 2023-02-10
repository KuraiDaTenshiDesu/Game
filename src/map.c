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

Texture2D grass;
Texture2D stone;

void Map_Prepare(int x, int y)
{
    grass = LoadTexture("img/grass.png");
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
            int r = rand() % 2 + 1;
            Map.matrix[x * Map.pair.x + y] = r;
        }
    }
}

Texture2D current;
void Map_Draw(int tileSize)
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
                current = grass;
            }

            DrawTexture(current, x * tileSize, y * tileSize, WHITE);
        }
    }
}