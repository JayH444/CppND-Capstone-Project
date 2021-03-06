#ifndef GameEntity_H
#define GameEntity_H

#include "SDL.h"
#include "util.h"

// Generic game entity.

class GameEntity {
public:
	GameEntity();
	~GameEntity();

	virtual bool CheckBoundingBoxCollision(GameEntity* target);

	// Getters / Setters:

	virtual SDL_Texture* GetTexture() const { return _texture; }
	virtual IntVector2 GetTextureDimensions() { return _textureDimensions; }
	virtual IntVector2 GetCollisionDimensions() { return _collisionDimensions; }
	virtual float GetX() const { return _x; }
	virtual float GetY() const { return _y; }
	virtual float GetCenterX() const { return _x + _textureDimensions._x / 2; }
	virtual float GetCenterY() const { return _y + _textureDimensions._y / 2; }
	virtual float GetSideX(bool side);
	virtual float GetSideY(bool side);
	virtual float GetCollisionLeft() { return GetSideX(false); }
	virtual float GetCollisionRight() { return GetSideX(true); }
	virtual float GetCollisionTop() { return GetSideY(false); }
	virtual float GetCollisionBottom() { return GetSideY(true); }
	virtual float GetVelocityX() const { return _velocityX; }  // In pixels/second
	virtual float GetVelocityY() const { return _velocityY; }  // In pixels/second
	virtual bool GetIsAlive() const { return _alive; }
	//
	virtual void SetTexture(SDL_Texture* t) { _texture = t; }
	virtual void SetTextureDimensions(int w, int h) { _textureDimensions = IntVector2(w, h); }
	virtual void SetCollisionDimensions(int w, int h) { _collisionDimensions = IntVector2(w, h); }
	virtual void SetX(float x) { _x = x; }
	virtual void SetY(float y) { _y = y; }
	virtual void SetMovementX(float x, float inertia);  // In pixels/second
	virtual void SetMovementY(float y, float inertia);  // In pixels/second
	virtual void SetIsAlive(bool alive) { _alive = alive; }

protected:
	SDL_Texture* _texture;
	IntVector2 _textureDimensions;
	IntVector2 _collisionDimensions;
	float _x;
	float _y;
	float _velocityX;
	float _velocityY;
	bool _alive;  // Used for cleanup if an object is considered "destroyed" or "dead"

};

#endif