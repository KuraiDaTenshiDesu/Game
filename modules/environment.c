#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct 
{
    char* texture;
    char* type;
} Environment;

void Environment_Place()
{
    srand(time(NULL));
    int n = rand() - 6 + 1;
    printf("%d", n);
}