#pragma once
#include "Enemy.h"

class FlyingEnemy : public Enemy
{

public:
    FlyingEnemy();
    void Activate(Vector2 startPos) override;

};
