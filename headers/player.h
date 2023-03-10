#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

extern int framesDelay;
extern int frameCounter;
extern int maxAtlasFrames;
extern int atlasX;
extern int atlasY;

void Player_Init(Vector2 coordinates, float speed, Texture2D atlas);
void Player_Move(char * map);
void Player_Draw();
Vector2 Player_GetCoordinates();
#endif