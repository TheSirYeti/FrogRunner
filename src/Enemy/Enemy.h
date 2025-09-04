#pragma once
#include "raylib.h"

class Enemy
{
protected:
    Vector2 position;
    float speed;
    Texture2D sprite;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float frameTime;
    float frameTimer;
    bool active = false;

public:
    Enemy();
    virtual ~Enemy() = default;

    virtual void Update();
    virtual void Draw();
    virtual void LoadSprite(const char* filepath, int frameCount, float frameRate);
    virtual void Unload();

    virtual void Activate(Vector2 startPos);
    bool IsActive() const { return active; }

    virtual Rectangle GetCollisionRect() const {
        return { position.x, position.y, 20, 20};
    }
};

