#include "SDL.h"

class Renderer {
public:
	Renderer(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	~Renderer();

	void Render();
	void UpdateWindowTitle();  // Might not be needed...

private:
	SDL_Window *_Window;
	SDL_Renderer *_Renderer;

	const int _ScreenWidth;
	const int _ScreenHeight;
};