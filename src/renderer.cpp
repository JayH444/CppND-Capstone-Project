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

void Renderer::LoadTexture(std::string filePath) {
	// Used for loading textures to be used by the renderer at some point, and setting up the 
	// information vector for their associated filename, and hashmap for their associated dimensions.
	if (_loadedTexturesHashMap.find(filePath) == _loadedTexturesHashMap.end()) {
		SDL_Surface* loadedSprite = SDL_LoadBMP(filePath.c_str());
		SDL_Texture* t;
		if (loadedSprite == nullptr) {
			ThrowError("\"" + filePath + "\" failed to load!");
		}
		else {
			SDL_SetColorKey(loadedSprite, SDL_TRUE, SDL_MapRGB(loadedSprite->format, 0xFF, 0x0, 0xFF));
			t = SDL_CreateTextureFromSurface(GetRenderer(), loadedSprite);

			// Emplace the associated dimensions of a filepath + name...
			IntVector2 textureDimensions = IntVector2(loadedSprite->w, loadedSprite->h);
			_loadedTexturesDimensionsHashMap.emplace(filePath, textureDimensions);

			// Emplace the associated filepath + name with a loaded texture...
			_loadedTexturesHashMap.emplace(filePath, t);
			_loadedTexturesKeys.emplace_back(filePath);
			SDL_FreeSurface(loadedSprite);
		}
	}
}

void Renderer::RenderTexture(SDL_Texture* t, SDL_Rect* r) {
	SDL_RenderCopy(_Renderer, t, nullptr, r);
}

void Renderer::Render(Player *p, std::vector<std::shared_ptr<GameObject>>* objects) {
	SDL_SetRenderDrawColor(_Renderer, 0x0F, 0x05, 0x0F, 0xFF);
	SDL_RenderClear(_Renderer);


	for (int i = 0; i < objects->size(); i++) {
		if (objects->at(i) == nullptr) {
			std::cout << "Object in _objects was nullptr!\n";
			continue;
		}
		int tW = objects->at(i)->GetTextureDimensions()._x;
		int tH = objects->at(i)->GetTextureDimensions()._y;
		SDL_Rect renderQuad = { (int)objects->at(i)->GetX(), (int)objects->at(i)->GetY(), tW, tH };
		RenderTexture(objects->at(i)->GetTexture(), &renderQuad);
	}

	int tW = p->GetTextureDimensions()._x;
	int tH = p->GetTextureDimensions()._y;
	SDL_Rect renderQuad = { (int)p->GetX(), (int)p->GetY(), tW, tH };
	RenderTexture(p->GetTexture(), &renderQuad);

	SDL_RenderPresent(_Renderer);
}

void Renderer::UpdateWindowTitle(int fps) {
	std::string title{ "Tyrianoid - FPS: " + std::to_string(fps) };
	SDL_SetWindowTitle(_Window, title.c_str());
}