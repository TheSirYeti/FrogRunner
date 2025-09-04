#include "Terrain.h"

Terrain::Terrain()
{
    scrollOffset = 0.0f;
    scrollSpeed = 100.0f;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
}

void Terrain::LoadTile(const char* filepath, float speed)
{
    tile = LoadTexture(filepath);
    tileSize = tile.width;
    scrollSpeed = speed;
}

void Terrain::Update()
{
    scrollOffset += scrollSpeed * GetFrameTime();

    if (scrollOffset >= tileSize)
        scrollOffset = 0.0f;
}

void Terrain::Draw()
{
    DrawTexture(tile, 100, 500, WHITE); // hardcoded position
    
    int columns = screenWidth / tileSize + 2; // +2 for buffer
    int rows = 1;  // ground only

    for (int i = 0; i < columns; i++)
    {
        float x = i * tileSize - scrollOffset;
        float y = screenHeight - tileSize;

        DrawTexture(tile, (int)x, (int)y, WHITE);
    }
}

void Terrain::Unload()
{
    UnloadTexture(tile);
}
