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

void Player::Update(double deltaTimeSeconds) {
	if (abs(GetVelocityX()) > 0 || abs(GetVelocityY()) > 0) {
		SetX(GetX() + GetVelocityX() * deltaTimeSeconds);
		SetY(GetY() + GetVelocityY() * deltaTimeSeconds);
	}

	if (HasMovementInput()) {

		// Calculate the X and Y component for all directions of movement, including diagonal:
		float changeX = 0;
		float changeY = 0;
		if (HasMovementInput()) {
			float angle = SDL_atan2f(GetInputX(), GetInputY());
			changeX = SDL_cosf(angle);
			changeY = SDL_sinf(angle);
		}

		SetMovementX(changeX * (float)_moveSpeed, 1);
		SetMovementY(changeY * (float)_moveSpeed, 1);
	}
	else {
		DecayVelocity(deltaTimeSeconds);
	}
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