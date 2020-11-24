#include "player.h"


Player::Player() : _moveSpeed(500), _inputX(0), _inputY(0) {
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

void Player::SetX(float x) {
	int w = GetCollisionDimensions()._x;
	int diff = GetTextureDimensions()._x - w;
	if (x + w + diff/2 > SCREEN_WIDTH) {
		_x = SCREEN_WIDTH - w - diff/2;
	}
	else if (x < 0 - diff/2) {
		_x = 0 - diff/2;
	}
	else {
		_x = x;
	}
}

void Player::SetY(float y) {
	int h = GetCollisionDimensions()._y;
	int diff = GetTextureDimensions()._y - h;
	if (y + h + diff/2 > SCREEN_HEIGHT) {
		_y = SCREEN_HEIGHT - h - diff/2;
	}
	else if (y < 0 - diff/2) {
		_y = 0 - diff/2;
	}
	else {
		_y = y;
	}

}