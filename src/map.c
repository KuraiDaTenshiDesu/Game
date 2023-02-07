#include <stdio.h>
#include <stdlib.h>

#include "pair.h"

struct
{
    Pair pair;
    char *matrix;
} Map;

void Map_Prepare(int x, int y)
{
    Map.pair.x = x;
    Map.pair.y = y;
    Map.matrix = (char *)malloc(sizeof(char) * x * y);
}

void Map_Fill()
{
    for (int x = Map.pair.x - 1; x >= 0; x--)
    {
        for (int y = Map.pair.y - 1; y >= 0; y--)
        {
            Map.matrix[x * Map.pair.x + y] = 'O';
        }
    }
}

void Map_Draw()
{
    for (int x = Map.pair.x - 1; x >= 0; x--)
    {
        for (int y = Map.pair.y - 1; y >= 0; y--)
        {
            printf("%c ", Map.matrix[x * Map.pair.x + y]);
        }
        printf("\n");
    }
}