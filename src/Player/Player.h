#pragma once
#include "raylib.h"

class Player
{
private:
    Vector2 position;
    Vector2 originalPosition;
    
    float jumpForce;
    bool isJumping = false;
    bool jumpHeld = false;
    float gravity;
    float velocityY;
    float jumpTime;
    float maxJumpTime;
    
    Texture2D sprite;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float frameTime;
    float frameTimer;

    
public:
    Player();
    void Unload();
    void Update();
    void Draw();
    void Reset();
    
    void SetPosition(Vector2 newPosition) { position = newPosition; }
    Vector2 GetPosition() { return position; }

    Texture2D GetSprite() { return sprite; }

    void Jump(bool holding);
    void SetJumpVelocity(float newVelocity) { jumpForce = newVelocity; }
    float GetJumpVelocity() { return jumpForce; }

    void LoadSprite(const char* filepath, int frameCount, float frameRate);

    Rectangle GetCollisionRect() const {
        return { position.x, position.y, (float)frameWidth, (float)frameHeight };
    }

};
