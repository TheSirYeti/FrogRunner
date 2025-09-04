#include "Enemy/Enemy.h"

Enemy::Enemy()
{
    position.x = GetScreenWidth() + 10;
    position.y = 400;

    speed = 200;
}
void Enemy::Activate(Vector2 startPos)
{
    position = startPos;
    active = true;
}

void Enemy::Update()
{
    if (!active) return;

    position.x -= speed * GetFrameTime();

    if (position.x + frameWidth < 0)
        active = false;
}

void Enemy::Draw()
{
    if (!active) return;

    frameTimer += GetFrameTime();
    if (frameTimer >= frameTime)
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    Rectangle sourceRec = { (float)(currentFrame * frameWidth), 0, (float)frameWidth, (float)frameHeight };
    DrawTextureRec(sprite, sourceRec, position, WHITE);
}


void Enemy::LoadSprite(const char* filepath, int frameCount, float frameRate)
{
    sprite = LoadTexture(filepath);
    totalFrames = frameCount;
    frameWidth = sprite.width / frameCount;
    frameHeight = sprite.height;
    frameTime = 1.0f / frameRate;
    frameTimer = 0.0f;
    currentFrame = 0;
}

void Enemy::Unload()
{
    active = false;
    position = { (float)GetScreenWidth() + 10, 400 }; // Off-screen reset
    currentFrame = 0;
    frameTimer = 0.0f;
}



