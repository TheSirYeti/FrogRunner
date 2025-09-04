#include <cstdio>

#include "raylib.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Terrain/Background.h"
#include "Terrain/Terrain.h"

const int ScreenWidth = 640;
const int ScreenHeight = 480;

enum class GameState
{
	StartScreen,
	Playing,
	GameOver
};

float metersRan = 0.0f;

// --- Function Prototypes ---
void ShowStartScreen(GameState& state);
void RunGame(GameState& state, Player& player, EnemyManager& enemyManager, Terrain& terrain);
void ShowGameOverScreen(GameState& state);

// --- Main ---
int main()
{
	InitWindow(ScreenWidth, ScreenHeight, "Run Frog, Run!");
	SetTargetFPS(60);

	GameState state = GameState::StartScreen;

	Player player;
	EnemyManager enemyManager;
	Background background;
	Terrain terrain;


	// Load assets once
	player.LoadSprite("src/Sprites/frog_run.png", 12, 24);
	enemyManager.Load();
	background.LoadTile("src/Sprites/background.png", 20);
	terrain.LoadTile("src/Sprites/floor_tiles.png", 200);
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BEIGE);

		background.Update();
		background.Draw();
		
		switch (state)
		{
		case GameState::StartScreen:
			player.Reset();
			enemyManager.Reset();
			ShowStartScreen(state);
			break;

		case GameState::Playing:
			RunGame(state, player, enemyManager, terrain);
			break;

		case GameState::GameOver:
			ShowGameOverScreen(state);
			break;
		}

		EndDrawing();
	}

	UnloadTexture(player.GetSprite());
	CloseWindow();
	return 0;
}

void RunGame(GameState& state, Player& player, EnemyManager& enemyManager, Terrain& terrain)
{
	// Input
	bool holding = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE);
	player.Jump(holding);

	//Terrain
	terrain.Update();
	terrain.Draw();

	// Update
	player.Update();
	player.Draw();

	enemyManager.Update();
	enemyManager.Draw();
	
	metersRan += 7.5f * GetFrameTime();  // Adjust 100.0f to control speed

	char buffer[32];
	sprintf(buffer, "Meters: %.0f m", metersRan);
	DrawText(buffer, 10, 10, 20, WHITE);

	// Check collision
	if (enemyManager.CheckCollisionWithPlayer(player))
	{
		state = GameState::GameOver;
	}
}

void ShowStartScreen(GameState& state)
{
	const char* title = "Run Frog, Run!";
	const char* buttonText = "Click here or JUMP to Start!";

	int fontSize = 40;
	int drawFontSize = 30; // actual font size used for drawing
	int textWidth = MeasureText(buttonText, drawFontSize);

	Rectangle button = {
		ScreenWidth / 2.0f - textWidth / 2.0f - 20,
		250,
		(float)textWidth + 40,
		60
	};

	bool hover = CheckCollisionPointRec(GetMousePosition(), button);

	DrawText(title, ScreenWidth / 2 - MeasureText(title, fontSize) / 2, 100, fontSize, DARKBROWN);

	DrawRectangleRec(button, hover ? DARKBROWN : BROWN);
	DrawText(buttonText, ScreenWidth / 2 - textWidth / 2, 270, drawFontSize, WHITE);

	const char* instructionText = "Use W / Up Arrow / Space to Jump";
	int instructionFontSize = 20;
	int instructionWidth = MeasureText(instructionText, instructionFontSize);

	DrawText(
		instructionText,
		ScreenWidth / 2 - instructionWidth / 2,
		button.y + button.height + 20,  // Position below the button
		instructionFontSize,
		DARKBROWN
	);


	if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
	{
		state = GameState::Playing;
	}
}

void ShowGameOverScreen(GameState& state)
{
	const char* loseText = "Game Over!";
	const char* restartText = "Press Jump or Click to Restart";

	DrawText(loseText, ScreenWidth / 2 - MeasureText(loseText, 50) / 2, 200, 50, RED);
	DrawText(restartText, ScreenWidth / 2 - MeasureText(restartText, 20) / 2, 300, 20, DARKGRAY);

	char buffer[64];
	sprintf(buffer, "You ran %.0f meters!", metersRan);
	DrawText(buffer, ScreenWidth / 2 - MeasureText(buffer, 30) / 2, ScreenHeight / 2 - 80, 30, WHITE);


	
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
	{
		metersRan = 0.0f;
		state = GameState::StartScreen;
	}
}

