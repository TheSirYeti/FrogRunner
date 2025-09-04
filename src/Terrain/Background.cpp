#include "Background.h"

#include <cmath>

Background::Background()
{
    scrollOffset = 0.0f;
    scrollSpeed = 30.0f; // slow upward scroll
    tileSize = 48;       // assuming your tile is 48x48
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
}

void Background::LoadTile(const char* filepath, float speed)
{
    tile = LoadTexture(filepath);
    tileSize = tile.width;
    scrollSpeed = speed;
}

void Background::Update()
{
    scrollOffset += scrollSpeed * GetFrameTime();

    if (scrollOffset >= tileSize)
        scrollOffset = 0.0f;
}

void Background::Draw()
{
    int columns = screenWidth / tileSize + 2;
    int rows = screenHeight / tileSize + 2;

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            float x = floorf(i * tileSize);
            float y = floorf(j * tileSize - scrollOffset);
            DrawTexture(tile, (int)x, (int)y, WHITE);

        }
    }
}

void Background::Unload()
{
    UnloadTexture(tile);
}
