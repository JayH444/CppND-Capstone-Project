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

void Renderer::LoadTextureForGameObject(GameObject* obj, std::string filePath) {
	if (_loadedTexturesHashMap.find(filePath) != _loadedTexturesHashMap.end()) {
		obj->SetTexture(_loadedTexturesHashMap[filePath]);
	}
	else {
		// Emplace the associated filepath + name with a loaded texture...
		SDL_Texture* t = LoadTexture(filePath);
		_loadedTexturesHashMap.emplace(filePath, t);
		obj->SetTexture(_loadedTexturesHashMap[filePath]);
		_loadedTexturesKeys.emplace_back(filePath);

		// Emplace the associated dimensions of a filepath + name...
		int w, h;
		SDL_QueryTexture(t, nullptr, nullptr, &w, &h);
		Vector2 textureDimensions = Vector2(w, h);
		_loadedTexturesDimensionsHashMap.emplace(filePath, textureDimensions);
	}
	if (obj->GetTexture() == nullptr) {
		ThrowError("Unable to create texture from " + filePath + "!");
	}
}

SDL_Texture* Renderer::LoadTexture(std::string filePath) {
	// Used for just loading textures to be used by the renderer at some point.
	if (_loadedTexturesHashMap.find(filePath) != _loadedTexturesHashMap.end()) {
		// If the texture has already been loaded...
		return _loadedTexturesHashMap[filePath];
	}
	SDL_Surface* loadedSprite = SDL_LoadBMP(filePath.c_str());
	SDL_Texture* t;
	if (loadedSprite == nullptr) {
		ThrowError("\"" + filePath + "\" failed to load!");
	}
	else {
		SDL_SetColorKey(loadedSprite, SDL_TRUE, SDL_MapRGB(loadedSprite->format, 0xFF, 0x0, 0xFF));
		t = SDL_CreateTextureFromSurface(GetRenderer(), loadedSprite);
		SDL_FreeSurface(loadedSprite);
	}
	return std::move(t);
}

void Renderer::RenderTexture(SDL_Texture* t, SDL_Rect* r) {
	SDL_RenderCopy(_Renderer, t, nullptr, r);
}

void Renderer::Render(Player *p) {
	SDL_SetRenderDrawColor(_Renderer, 0x0F, 0x05, 0x0F, 0xFF);
	SDL_RenderClear(_Renderer);

	int pW = p->GetTextureDimensions()._x;
	int pH = p->GetTextureDimensions()._y;
	SDL_Rect renderQuad = { (int)p->GetX(), (int)p->GetY(), pW, pH };
	RenderTexture(p->GetTexture(), &renderQuad);
	
	SDL_RenderPresent(_Renderer);
}

void Renderer::UpdateWindowTitle(int fps) {
	std::string title{ "Tyrianoid - FPS: " + std::to_string(fps) };
	SDL_SetWindowTitle(_Window, title.c_str());
}