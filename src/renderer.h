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

	void Render(Player *p, std::vector<std::shared_ptr<GameObject>> *objects);
	void UpdateWindowTitle(int fps, int score);
	void UpdateWindowTitle(std::string msg, int score);
	void LoadTexture(std::string filePath);
	void RenderTexture(SDL_Texture* t, SDL_Rect* r);
	void RenderCollisionBox(SDL_Rect* r);

	// Getters / Setters:

	SDL_Renderer* GetRenderer() const { return _Renderer; }

	std::unordered_map<std::string, SDL_Texture*> _loadedTexturesHashMap;
	std::unordered_map<std::string, IntVector2> _loadedTexturesDimensionsHashMap;
	std::vector<std::string> _loadedTexturesKeys;

private:
	SDL_Window* _Window;
	SDL_Renderer* _Renderer;
};

#endif