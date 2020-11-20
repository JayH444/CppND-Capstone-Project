#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"

// Generic game object.

class GameObject {
public:
	GameObject();
	~GameObject();

	// Getters / Setters:

	virtual SDL_Texture* GetTexture() const { return _texture; }
	virtual void SetTexture(SDL_Texture* t) { _texture = t; }
protected:
	SDL_Texture* _texture;
};

#endif