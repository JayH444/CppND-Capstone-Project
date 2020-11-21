#include "player.h"


Player::Player() : _moveSpeed(500) {
}

void Player::SetMovementDirection(const Uint8* keystate) {
	if (keystate[SDL_SCANCODE_W]) _inputX = -1;
	if (keystate[SDL_SCANCODE_S]) _inputX = 1;
	// Holding neither direction or both simultaneously will cancel the movement:
	if (keystate[SDL_SCANCODE_W] == keystate[SDL_SCANCODE_S]) _inputX = 0;

	if (keystate[SDL_SCANCODE_A]) _inputY = -1;
	if (keystate[SDL_SCANCODE_D]) _inputY = 1;
	// Ditto:
	if (keystate[SDL_SCANCODE_A] == keystate[SDL_SCANCODE_D]) _inputY = 0;
}