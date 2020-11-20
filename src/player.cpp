#include "player.h"
#include "util.h"

Player::Player() : _sprite(nullptr) {
	_sprite = SDL_LoadBMP("textures/ship.bmp");
	if (_sprite == nullptr) {
		ThrowError("Player sprite failed to load!");
	}
	SDL_SetColorKey(_sprite, SDL_TRUE, SDL_MapRGB(_sprite->format, 0xFF, 0x0, 0xFF));
}

Player::~Player() {
	SDL_FreeSurface(_sprite);
	_sprite = nullptr;
}