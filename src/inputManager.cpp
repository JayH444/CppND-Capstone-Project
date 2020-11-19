#include "SDL.h"
#include <iostream>

#include "inputManager.h"

void InputManager::HandleInput(bool& running) const {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
	}
}