#include "Enemy/EnemyManager.h"

#include <iostream>
#include <valarray>

#include "raylib.h"
#include "FlyingEnemy.h"  // include new type

void EnemyManager::Load()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        // 50/50 chance to create a FlyingEnemy or normal one
        if (GetRandomValue(0, 1) == 0)
        {
            enemies[i] = new Enemy();
            enemies[i]->LoadSprite("src/Sprites/runner.png", 12, 24);
        }
        else
        {
            enemies[i] = new FlyingEnemy();
            enemies[i]->LoadSprite("src/Sprites/bird.png", 4, 8);
        }
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
            if (!enemies[i]->IsActive())
            {
                Vector2 startPos = {
                    (float)GetScreenWidth() + 10,
                    400 // default position, overridden by FlyingEnemy
                };
                enemies[i]->Activate(startPos);
                break;
            }
        }
        
        float rand = (float)GetRandomValue((int)(-spawnIntervalRand * 1000), (int)(spawnIntervalRand * 1000)) / 1000.0f;
        spawnTimer = spawnInterval + rand;

        if (spawnTimer < 0.1f)
            spawnTimer = 0.1f;

    }
}

void EnemyManager::Draw()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i]->Update();
        enemies[i]->Draw();
    }

}

bool EnemyManager::CheckCollisionWithPlayer(const Player& player)
{
    Rectangle playerRect = player.GetCollisionRect();

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i]->IsActive())
        {
            if (CheckCollisionRecs(enemies[i]->GetCollisionRect(), playerRect))
            {
                return true;
            }
        }
    }

    return false;
}

void EnemyManager::Reset()
{
    // Delete existing enemies
    for (int i = 0; i < MAX_ENEMIES; ++i)
    {
        delete enemies[i];
        enemies[i] = nullptr;
    }

    // Re-randomize enemy types
    RebuildEnemies();

    spawnTimer = 0.0f;
}

void EnemyManager::RebuildEnemies()
{
    for (int i = 0; i < MAX_ENEMIES; ++i)
    {
        if (GetRandomValue(0, 1) == 0)
        {
            enemies[i] = new Enemy();
            enemies[i]->LoadSprite("src/Sprites/runner.png", 12, 24);
        }
        else
        {
            enemies[i] = new FlyingEnemy();
            enemies[i]->LoadSprite("src/Sprites/bird.png", 4, 8);
        }
    }
}



