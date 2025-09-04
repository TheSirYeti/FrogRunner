#include "Enemy/EnemyManager.h"

#include <iostream>
#include <valarray>

#include "raylib.h"

void EnemyManager::Load(const char* filepath, int frameCount, float frameRate)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i] = Enemy();
        enemies[i].LoadSprite(filepath, frameCount, frameRate);
    }
}

void EnemyManager::Update()
{
    spawnTimer -= GetFrameTime();

    if (spawnTimer <= 0)
    {
        spawnTimer = 99999;
        // Try to spawn one enemy
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (!enemies[i].IsActive())
            {
                Vector2 startPos = {
                    (float)GetScreenWidth() + 10,
                    400  // same Y as your original enemy
                };
                enemies[i].Activate(startPos);
                break;
            }
        }
        
        float rand = (float)GetRandomValue((int)(-spawnIntervalRand * 1000), (int)(spawnIntervalRand * 1000)) / 1000.0f;
        spawnTimer = spawnInterval + rand;

        if (spawnTimer < 0.1f)
            spawnTimer = 0.1f;

    }

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].Update();
    }
}

void EnemyManager::Draw()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].Draw();
    }
}

bool EnemyManager::CheckCollisionWithPlayer(const Player& player)
{
    Rectangle playerRect = player.GetCollisionRect();

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].IsActive())
        {
            if (CheckCollisionRecs(enemies[i].GetCollisionRect(), playerRect))
            {
                return true;
            }
        }
    }

    return false;
}

void EnemyManager::Reset()
{
    for (int i = 0; i < MAX_ENEMIES; ++i)
    {
        enemies[i].Unload();
    }

    spawnTimer = 0.0f;
}

