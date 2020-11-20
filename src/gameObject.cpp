#include "gameObject.h"

// This is the generic game object type that all objects in the game world should inherit from.

GameObject::GameObject() : _texture(nullptr) {
}

GameObject::~GameObject() {
	_texture = nullptr;
}