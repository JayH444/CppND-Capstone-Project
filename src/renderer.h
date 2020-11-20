#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include <iostream>
#include <string>
#include <vector>

#include "player.h"

class Renderer {
public:
	Renderer(const int screenWidth, const int screenHeight);
	~Renderer();

	void Render(Player *p);
	void UpdateWindowTitle(int fps);

private:
	SDL_Window* _Window;
	SDL_Surface* _Surface;
	SDL_Renderer* _Renderer;

	const int _ScreenWidth;
	const int _ScreenHeight;
};

#endif