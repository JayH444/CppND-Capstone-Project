#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "util.h"

#include "player.h"
#include "gameObject.h"

class Renderer {
public:
	Renderer(const int screenWidth, const int screenHeight);
	~Renderer();

	void Render(Player *p);
	void UpdateWindowTitle(int fps);
	void LoadTextureForGameObject(GameObject* obj, std::string filePath);
	SDL_Texture* LoadTexture(std::string filePath);
	void RenderTexture(SDL_Texture* t, SDL_Rect* r);

	// Getters / Setters:

	SDL_Renderer* GetRenderer() const { return _Renderer; }

	std::unordered_map<std::string, SDL_Texture*> _loadedTexturesHashMap;
	std::unordered_map<std::string, Vector2> _loadedTexturesDimensionsHashMap;
	std::vector<std::string> _loadedTexturesKeys;

private:
	SDL_Window* _Window;
	SDL_Renderer* _Renderer;
	const int _ScreenWidth;
	const int _ScreenHeight;
};

#endif