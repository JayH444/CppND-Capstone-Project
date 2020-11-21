#include <SDL.h>
#include <iostream>

#include "gameManager.h"

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

	// Credits to Brandon Foltz for their implementation of delta time, and Patrick le Duc of stackexchange/stackoverflow
	// for their version of it using SDL_GetPerformanceCounter().
	// November 2020,
	// https://carlopsite.files.wordpress.com/2017/08/the_game_loop_and_frame_rate_management.pdf
	// https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl

	Uint64 frameTimeStart = 0;  // Time at the start of a frame.
	Uint64 frameTimeEnd = 0;  // Time at the end of a frame.
	float frameDeltaTime = 0;  // Time since start of frame.
	float deltaTimeSeconds = 0;
	// ALL game actions where applicible should be scaled by deltaTimeSeconds to ensure they're being executed at the 
	// same speed regardless of framerate.

	int targetFramerate = 300;
	int targetMsPerFrame = 1000 / targetFramerate;

	while (running) {

		frameTimeStart = SDL_GetPerformanceCounter();


		// Handle inputs:
		inputManager->HandleInput(running, _playerActor.get());

		// Update game state:
		deltaTimeSeconds = (float)frameDeltaTime / 1000.0f;

		if (_playerActor->HasMovementInput()) {

			float angle = SDL_atan2f(_playerActor->GetInputX(), _playerActor->GetInputY());
			float changeX = SDL_cosf(angle);
			float changeY = SDL_sinf(angle);

			_playerActor->SetX(_playerActor->GetX() + changeX * (float)_playerActor->_moveSpeed * deltaTimeSeconds);
			_playerActor->SetY(_playerActor->GetY() + changeY * (float)_playerActor->_moveSpeed * deltaTimeSeconds);
		}

		// Render:
		renderer->Render(_playerActor.get());


		frameTimeEnd = SDL_GetPerformanceCounter();
		frameDeltaTime = (double)(frameTimeEnd - frameTimeStart) * 1000.0 / SDL_GetPerformanceFrequency();

		if (frameDeltaTime < 1 || frameDeltaTime > 1000) {
			frameTimeStart = SDL_GetPerformanceCounter();
			SDL_Delay(targetMsPerFrame);
			frameTimeEnd = SDL_GetPerformanceCounter();
			frameDeltaTime = (double)(frameTimeEnd - frameTimeStart) * 1000.0 / SDL_GetPerformanceFrequency();
			renderer->UpdateWindowTitle(1000 / frameDeltaTime);
		}
	}
}