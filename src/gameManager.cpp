#include <SDL.h>
#include <iostream>

#include "gameManager.h"
#include "util.h"

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::Run(InputManager const* inputManager, Renderer* renderer) {
	bool running = true;

	// Create the player:
	_playerActor = std::unique_ptr<Player>(new Player());
	std::string filePath = "textures/ship.bmp";
	renderer->LoadTexture(_playerActor.get(), filePath);

	Uint32 frameTimeStart;  // Time at the start of a frame.
	Uint32 frameTimeEnd;  // Time at the end of a frame.
	Uint32 frameDeltaTime;  // Time since start of frame.
	// ALL game actions where applicible should be scaled by deltaTime to ensure they're being executed at the same speed regardless of framerate.

	Uint32 frameCount = 0;
	Uint32 FPSTimestamp = SDL_GetTicks();

	float targetFramerate = 300.0;
	float targetMsPerFrame = 1000.0 / targetFramerate;

	while (running) {

		frameTimeStart = SDL_GetTicks();

		inputManager->HandleInput(running);
		renderer->Render(_playerActor.get());

		frameTimeEnd = SDL_GetTicks();
		frameDeltaTime = frameTimeEnd - frameTimeStart;
		frameCount++;

		if (frameTimeEnd - FPSTimestamp >= 1000) {
			renderer->UpdateWindowTitle(frameCount);
			frameCount = 0;
			FPSTimestamp = frameTimeEnd;
		}

		if (frameDeltaTime < (Uint32)targetMsPerFrame) {
			SDL_Delay((Uint32)targetMsPerFrame - frameDeltaTime);
		}
	}
}