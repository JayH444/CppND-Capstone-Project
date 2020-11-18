//Using SDL and the standard C++ IO stream:
#include <SDL.h>
#include <iostream>

// Credits to Lazy Foo's tutorials for their SDL game dev content, and some code snippets!
// November 2020, https://lazyfoo.net/tutorials/SDL/index.php

// Constants:
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {  // Note that unless you use "#undef main", ( int argc, char* args[] ) must be the args for main().
	// The window being rendered to:
	SDL_Window* window = NULL;

	// The surface contained by the window:
	SDL_Surface* screenSurface = NULL;

	bool running = true;

	// Initializing SDL:
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Couldn't initialize SDL! SDL_Error: " << SDL_GetError() << '\n';
	}
	else {
		// Create the window:
		window = SDL_CreateWindow("Tyrianoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		while (running) {
			// Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Update the surface
			SDL_UpdateWindowSurface(window);
		}
	}

	// Clean up SDL window, and quit the SDL subsystems before exiting:
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}