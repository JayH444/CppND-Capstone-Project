#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include "SDL.h"

class Renderer {
public:
	Renderer(const int screenWidth, const int screenHeight);
	~Renderer();

	void Render();
	void UpdateWindowTitle();  // Might not be needed...
	void ThrowError(std::string msg);

private:
	SDL_Window *_Window;
	SDL_Renderer *_Renderer;

	const int _ScreenWidth;
	const int _ScreenHeight;
};

#endif