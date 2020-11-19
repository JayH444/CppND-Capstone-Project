#include <SDL.h>
#include <iostream>

#include "gameManager.h"

GameManager::GameManager() {

}

void GameManager::Run(InputManager const& inputManager, Renderer& renderer) {
	bool running = true;

	while (running) {
		inputManager.HandleInput(running);
		renderer.Render();
	}
}