#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include <iostream>
#include <string>
#include <vector>

#include "util.h"
#include "player.h"

class Renderer {
public:
	Renderer(const int screenWidth, const int screenHeight);
	~Renderer();

	void Render(Player *p);
	void UpdateWindowTitle(int fps);
	void LoadTexture(GameObject* obj, std::string filePath);
	void RenderTexture(SDL_Texture* t, SDL_Rect* r);

	// Getters / Setters:

	SDL_Renderer* GetRenderer() const { return _Renderer; }

private:
	SDL_Window* _Window;
	SDL_Renderer* _Renderer;
	const int _ScreenWidth;
	const int _ScreenHeight;
};

#endif