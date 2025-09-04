#pragma once
#include "Player.h"

Player::Player()
{
    position.x = 100;
    position.y = 400;

    originalPosition = position;

    jumpForce = 250;

    gravity = 1000.0f;
    velocityY = 0.0f;
    jumpTime = 0.0f;
    maxJumpTime = 0.5f;
}

void Player::Update()
{
    float dt = GetFrameTime();

    if (isJumping)
    {
        if (jumpHeld && jumpTime < maxJumpTime)
        {
            velocityY = -jumpForce;
            jumpTime += dt;
        }
        else
        {
            isJumping = false;
        }
    }
    
    velocityY += gravity * dt;
    position.y += velocityY * dt;
    
    if (position.y >= originalPosition.y)
    {
        position.y = originalPosition.y;
        velocityY = 0;
        isJumping = false;
    }
}

void Player::Draw()
{
    frameTimer += GetFrameTime();
    if (frameTimer >= frameTime)
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }

    Rectangle sourceRec = { (float)(currentFrame * frameWidth), 0, (float)frameWidth, (float)frameHeight };

    DrawTextureRec(sprite, sourceRec, position, WHITE);
}

void Player::Jump(bool holding)
{
    jumpHeld = holding;

    if (holding && !isJumping && position.y >= originalPosition.y)
    {
        isJumping = true;
        jumpTime = 0.0f;
        velocityY = -jumpForce;
    }
}

void Player::LoadSprite(const char* filepath, int frameCount, float frameRate)
{
    sprite = LoadTexture(filepath);
    totalFrames = frameCount;
    frameWidth = sprite.width / frameCount;
    frameHeight = sprite.height;
    frameTime = 1.0f / frameRate;
    frameTimer = 0.0f;
    currentFrame = 0;
}

void Player::Unload()
{
    UnloadTexture(sprite);
}

void Player::Reset()
{
    position = { 100, 400 }; // Adjust this to your desired start position
    isJumping = false;
    jumpTime = 0;
    currentFrame = 0;
    frameTimer = 0.0f;
}

