#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "util.h"

// Generic game object.

class GameObject {
public:
	GameObject();
	//GameObject(SDL_Texture*, Vector2 textureD, Vector2 collisionD, int x, int y);
	~GameObject();

	virtual void DecayVelocity(float deltaTime);

	// Getters / Setters:

	virtual SDL_Texture* GetTexture() const { return _texture; }
	virtual Vector2 GetTextureDimensions() { return _textureDimensions; }
	virtual Vector2 GetCollisionDimensions() { return _collisionDimensions; }
	virtual float GetX() const { return _x; }
	virtual float GetY() const { return _y; }
	virtual float GetVelocityX() const { return _velocityX; }  // In pixels/second
	virtual float GetVelocityY() const { return _velocityY; }  // In pixels/second
	virtual float GetMovementMagnitude() const;
	virtual float GetMovementDirection() const;
	//
	virtual void SetTexture(SDL_Texture* t) { _texture = t; }
	virtual void SetTextureDimensions(int w, int h) { _textureDimensions = Vector2(w, h); }
	virtual void SetCollisionDimensions(int w, int h) { _collisionDimensions = Vector2(w, h); }
	virtual void SetX(float x) { _x = x; }
	virtual void SetY(float y) { _y = y; }
	virtual void SetMovementX(float x, float inertia);  // In pixels/second
	virtual void SetMovementY(float y, float inertia);  // In pixels/second

protected:
	SDL_Texture* _texture;
	Vector2 _textureDimensions;
	Vector2 _collisionDimensions;
	float _x;
	float _y;
	float _velocityX;
	float _velocityY;

};

#endif