#include "renderer.h"


Renderer::Renderer(const int screenWidth, const int screenHeight) : _ScreenWidth(screenWidth), _ScreenHeight(screenHeight) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ThrowError("Couldn't initialize SDL!");
	}

	// Create the window to render to:
	_Window = SDL_CreateWindow("Tyrianoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _ScreenWidth, _ScreenHeight, SDL_WINDOW_SHOWN);
	if (_Window == nullptr) {
		ThrowError("Window couldn't be created!");
	}

	// Create the renderer:
	_Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED);
	if (_Renderer == nullptr) {
		ThrowError("Renderer couldn't be created!");
	}
}

Renderer::~Renderer() {
	// Clean up SDL window, and quit the SDL subsystems:
	SDL_DestroyWindow(_Window);
	SDL_Quit();
}

void Renderer::ThrowError(std::string msg) {
	std::cerr << msg << '\n';
	std::cerr << "SDL_Error: " << SDL_GetError() << '\n';
}

void Renderer::Render() {
	SDL_SetRenderDrawColor(_Renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(_Renderer);

	// Do stuff here.

	SDL_RenderPresent(_Renderer);
}