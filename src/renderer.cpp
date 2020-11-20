#include "renderer.h"
#include "util.h"

Renderer::Renderer(const int screenWidth, const int screenHeight) : _ScreenWidth(screenWidth), _ScreenHeight(screenHeight) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ThrowError("Couldn't initialize SDL!");
	}

	// Create the window to render to:
	_Window = SDL_CreateWindow("Tyrianoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _ScreenWidth, _ScreenHeight, SDL_WINDOW_SHOWN);
	if (_Window == nullptr) {
		ThrowError("Renderer member variable _Window couldn't be created!");
	}

	_Surface = SDL_GetWindowSurface(_Window);
	if (_Surface == nullptr) {
		ThrowError("Renderer member variable _Surface couldn't be created!");
	}

	// Create the renderer:
	_Renderer = SDL_CreateRenderer(_Window, -1, SDL_RENDERER_ACCELERATED);
	if (_Renderer == nullptr) {
		ThrowError("Renderer member variable _Renderer couldn't be created!");
	}
}

Renderer::~Renderer() {
	// Clean up SDL window, and quit the SDL subsystems:
	SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
	SDL_Quit();
}

void Renderer::Render(Player *p) {
	//SDL_SetRenderDrawColor(_Renderer, 0x1E, 0x1E, 0x1E, 0xFF);

	// Do stuff here.
	SDL_Surface* playerSprite = p->GetSprite();

	SDL_BlitSurface(playerSprite, nullptr, _Surface, nullptr);

	SDL_UpdateWindowSurface(_Window);
	//SDL_RenderClear(_Renderer);
	//SDL_RenderPresent(_Renderer);
}

void Renderer::UpdateWindowTitle(int fps) {
	std::string title{ "Tyrianoid - FPS: " + std::to_string(fps) };
	SDL_SetWindowTitle(_Window, title.c_str());
}