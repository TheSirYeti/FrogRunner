#pragma once
#include "raylib.h"

class Terrain
{
private:
    Texture2D tile;
    float scrollOffset;
    float scrollSpeed;
    int tileSize;
    int screenWidth;
    int screenHeight;

public:
    Terrain();
    void LoadTile(const char* filepath, float speed);
    void Update();
    void Draw();
    void Unload();
};
