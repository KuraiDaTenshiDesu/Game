#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

Camera2D camera;

void Camera_Init(int w, int h)
{
    camera.offset = (Vector2){w / 2.0f, h / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Camera_SetTarget(Vector2 target)
{
    camera.target = target;
}

Camera2D Camera_GetCamera()
{
    return camera;
}
