#include "renderer.h"

Renderer::Renderer(const int screenWidth, const int screenHeight) : _ScreenWidth(screenWidth), _ScreenHeight(screenHeight) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ThrowError("Couldn't initialize SDL!");
	}

	// Create the window to render to:
	_Window = SDL_CreateWindow("Tyrianoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _ScreenWidth, _ScreenHeight, SDL_WINDOW_SHOWN);
	if (_Window == nullptr) {
		ThrowError("Renderer member variable _Window couldn't be created!");
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

void Renderer::LoadTexture(GameObject* obj, std::string filePath) {
	// Used for loading textures that will be used by the renderer.
	SDL_Surface* loadedSprite = SDL_LoadBMP(filePath.c_str());
	if (loadedSprite == nullptr) {
		ThrowError("\"" + filePath + "\" failed to load!");
	}
	else {
		SDL_SetColorKey(loadedSprite, SDL_TRUE, SDL_MapRGB(loadedSprite->format, 0xFF, 0x0, 0xFF));
		obj->SetTexture(SDL_CreateTextureFromSurface(GetRenderer(), loadedSprite));
		if (obj->GetTexture() == nullptr) {
			ThrowError("Unable to create texture from player sprite!");
		}

		// Delete the old loaded surface:
		SDL_FreeSurface(loadedSprite);
	}
}

void Renderer::RenderTexture(SDL_Texture* t, SDL_Rect* r) {
	SDL_RenderCopy(_Renderer, t, nullptr, r);
}

void Renderer::Render(Player *p) {
	SDL_SetRenderDrawColor(_Renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(_Renderer);

	SDL_Rect renderQuad = { (int)p->GetX(), (int)p->GetY(), 64, 64 };
	RenderTexture(p->GetTexture(), &renderQuad);
	
	SDL_RenderPresent(_Renderer);
}

void Renderer::UpdateWindowTitle(int fps) {
	std::string title{ "Tyrianoid - FPS: " + std::to_string(fps) };
	SDL_SetWindowTitle(_Window, title.c_str());
}