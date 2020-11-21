#include "gameObject.h"

// This is the generic game object type that all objects in the game world should inherit from.

GameObject::GameObject() : _texture(nullptr), _velocityX(0), _velocityY(0), _x(0), _y(0) {
}

GameObject::~GameObject() {
	_texture = nullptr;
}

float GameObject::GetMovementMagnitude() const {
	return SDL_sqrtf(SDL_pow(_velocityX, 2.0) + SDL_pow(_velocityY, 2.0));
}
float GameObject::GetMovementDirection() const {
	return RadToDeg(SDL_atan2f(_velocityX, _velocityY));
}