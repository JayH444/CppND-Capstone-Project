#include "util.h"

// Utility functions. util.h should generally be included in all of the game's header files as boilerplate.

void ThrowError(std::string msg) {
	SDL_SetError("SDL_Error: %s", msg.c_str());
	std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
}