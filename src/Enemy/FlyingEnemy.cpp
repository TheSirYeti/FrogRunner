#include "FlyingEnemy.h"
#include "raylib.h"

FlyingEnemy::FlyingEnemy() : Enemy(){}

void FlyingEnemy::Activate(Vector2 startPos)
{
    float minY = 150.0f;
    float maxY = 400.0f;

    position = {
        (float)GetScreenWidth() + 10.0f,
        (float)GetRandomValue((int)minY, (int)maxY)
    };

    active = true;
}

