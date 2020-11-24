#include "gameObject.h"

// This is the generic game object type that all objects in the game world should inherit from.

// Parameter-less constructor:
GameObject::GameObject() :
	_texture(nullptr),
	_textureDimensions(0, 0),
	_collisionDimensions(0, 0),
	_velocityX(0),
	_velocityY(0),
	_x(0),
	_y(0) {
}

GameObject::~GameObject() {
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}

float GameObject::GetMovementMagnitude() const {
	return SDL_sqrtf(SDL_pow(_velocityX, 2.0) + SDL_pow(_velocityY, 2.0));
}
float GameObject::GetMovementDirection() const {
	return RadToDeg(SDL_atan2f(_velocityX, _velocityY));
}

void GameObject::SetMovementX(float x, float inertia) {
	if (abs(_velocityX) < abs(x)) {
		_velocityX += x * inertia;
	}
	else {
		_velocityX = x;
	}
}

void GameObject::SetMovementY(float y, float inertia) {
	if (abs(_velocityY) < abs(y)) {
		_velocityY += y * inertia;
	}
	else {
		_velocityY = y;
	}
}

void GameObject::DecayVelocity(float deltaTime) {
	_velocityX *= 0;
	_velocityY *= 0;
}