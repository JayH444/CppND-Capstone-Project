#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "util.h"

// Generic game object.

class GameObject {
public:
	GameObject();
	~GameObject();

	// Getters / Setters:

	virtual SDL_Texture* GetTexture() const { return _texture; }
	virtual float GetX() const { return _x; }
	virtual float GetY() const { return _y; }
	virtual float GetVelocityX() const { return _velocityX; }  // In pixels/second
	virtual float GetVelocityY() const { return _velocityY; }  // In pixels/second
	virtual float GetMovementMagnitude() const;
	virtual float GetMovementDirection() const;
	//
	virtual void SetTexture(SDL_Texture* t) { _texture = t; }
	virtual void SetX(float x) { _x = x; }
	virtual void SetY(float y) { _y = y; }
	virtual void SetVelocityX(float x) { _velocityX = x; }  // In pixels/second
	virtual void SetVelocityY(float y) { _velocityY = y; }  // In pixels/second

protected:
	SDL_Texture* _texture;
	float _x;
	float _y;
	float _velocityX;
	float _velocityY;
};

#endif