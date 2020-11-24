#include "inputManager.h"

void InputManager::HandleInput(bool& running, Player* player) const {
	SDL_Event event;
	// SDL_Event shouldn't be used for player input. It's subject to OS keyboard repeat rates and can only detect
	// the key changing states (e.g. pressed/released). This will produce jerky, inconsistent inputs as a result.
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
	player->SetMovementDirection(keystate);
}