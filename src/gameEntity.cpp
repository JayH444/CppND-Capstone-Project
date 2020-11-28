#include "gameEntity.h"

// This is the generic game object type that all objects in the game world should inherit from.

// Parameter-less constructor:
GameEntity::GameEntity() :
	_texture(nullptr),
	_textureDimensions(0, 0),
	_collisionDimensions(0, 0),
	_velocityX(0),
	_velocityY(0),
	_x(0),
	_y(0),
	_alive(true) {
}

GameEntity::~GameEntity() {
	if (_texture != nullptr) {
		_texture = nullptr;
	}
}

float GameEntity::GetSideX(bool side) {
	// for the parameter side: true = right, false = left.
	float c = GetCenterX();
	float collisionSize = GetCollisionDimensions()._x / 2;
	return (side) ? c + collisionSize : c - collisionSize;
}

float GameEntity::GetSideY(bool side) {
	// for the parameter side: true = bottom, false = top.
	float c = GetCenterY();
	float collisionSize = GetCollisionDimensions()._y / 2;
	return (side) ? c + collisionSize : c - collisionSize;
}

void GameEntity::SetMovementX(float x, float inertia) {
	if (abs(_velocityX) < abs(x)) {
		_velocityX += x * inertia;
	}
	else {
		_velocityX = x;
	}
}

void GameEntity::SetMovementY(float y, float inertia) {
	if (abs(_velocityY) < abs(y)) {
		_velocityY += y * inertia;
	}
	else {
		_velocityY = y;
	}
}

bool GameEntity::CheckBoundingBoxCollision(GameEntity* target) {
	bool withinBoundsX = target->GetCollisionRight() > GetCollisionLeft() && target->GetCollisionLeft() < GetCollisionRight();
	bool withinBoundsY = target->GetCollisionBottom() > GetCollisionTop() && target->GetCollisionTop() < GetCollisionBottom();
	return (withinBoundsX && withinBoundsY);
}