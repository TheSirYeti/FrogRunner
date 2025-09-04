#pragma once
#include "Enemy.h"
#include "Player/Player.h"

const int MAX_ENEMIES = 10;

class EnemyManager
{
private:
    Enemy* enemies[MAX_ENEMIES];
    Texture2D enemyTexture;
    float spawnTimer = 0.0f;
    float spawnInterval = 2.0f;
    float spawnIntervalRand = 1.9f;

public:
    void Load();
    void Update();
    void Draw();
    void Reset();
    Texture2D GetEnemyTexture() { return enemyTexture; }
    bool CheckCollisionWithPlayer(const Player& player);

};
