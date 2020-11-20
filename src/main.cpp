//Using SDL and the standard C++ IO stream:
#include <SDL.h>
#include <iostream>
#include <memory>

// Game files:
#include "inputManager.h"
#include "gameManager.h"
#include "renderer.h"

// Credits to Lazy Foo's tutorials for their SDL game dev content, and some code snippets!
// November 2020, https://lazyfoo.net/tutorials/SDL/index.php


int main(int argc, char* args[]) {  // Note that unless you use "#undef main", the params ( int argc, char* args[] ) must be included for main().
	// Constants:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	auto renderer = std::unique_ptr<Renderer>(new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT));
	auto inputManager = std::unique_ptr<InputManager>(new InputManager());
	auto game = std::unique_ptr<GameManager>(new GameManager());

	game->Run(inputManager.get(), renderer.get());

	return 0;
}