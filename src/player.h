#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

class Player {
public:
	Player();
	~Player();
	void Update();

	SDL_Surface* GetSprite() const { return _sprite; }
private:
	SDL_Surface* _sprite;
};

#endif