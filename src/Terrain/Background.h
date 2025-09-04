#pragma once
#include "raylib.h"

class Background
{
private:
    Texture2D tile;
    float scrollOffset;
    float scrollSpeed;
    int tileSize;
    int screenWidth;
    int screenHeight;

public:
    Background();
    void LoadTile(const char* filepath, float speed);
    void Update();
    void Draw();
    void Unload();
};
