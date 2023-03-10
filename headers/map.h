#ifndef MAP_H
#define MAP_H

extern const int tileSizeDefault;
extern const int tilesCols;
extern const int tilesRows;
extern const int multiplyer;
extern const int maxMapSize;
extern const int tileSize;
extern char * map;

void Map_Init();
void Draw_Tiles(char *map);
bool Check_Collision(char * map, Vector2 coordinates);
#endif