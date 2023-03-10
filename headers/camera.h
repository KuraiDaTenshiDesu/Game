#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

void Camera_Init(int w, int h);
void Camera_SetTarget(Vector2 target);
Camera2D Camera_GetCamera();

#endif