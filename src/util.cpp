#include "util.h"

// Utility functions. util.h should generally be included in all of the game's header files as boilerplate.

void ThrowError(std::string msg) {
	//std::cerr << msg << '\n';
	SDL_SetError(msg.c_str());
	std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
}

float RadToDeg(float n) {
	return n * 180.0 / M_PI;
}

float DegToRad(float n) {
	return n * M_PI / 180.0;
}