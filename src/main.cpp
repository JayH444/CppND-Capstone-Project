//Using SDL + all the necessary standard library headers:
#include <SDL.h>
#include "util.h"

// Game files:
#include "inputManager.h"
#include "gameManager.h"
#include "renderer.h"

/*
Credits to Lazy Foo's tutorials for their SDL game dev content, and some code snippets!
November 2020, https://lazyfoo.net/tutorials/SDL/index.php
*/

int main(int argc, char* args[]) {
	// Note that unless you use "#undef main", the params ( int argc, char* args[] ) must be included for main().
	auto renderer = std::unique_ptr<Renderer>(new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT));
	auto inputManager = std::unique_ptr<InputManager>(new InputManager());
	auto game = std::unique_ptr<GameManager>(new GameManager());

	game->Run(inputManager.get(), renderer.get());

	return 0;
}