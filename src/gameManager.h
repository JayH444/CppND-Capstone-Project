#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <random>
#include "SDL.h"
#include "inputManager.h"
#include "renderer.h"

class GameManager {
public:
	GameManager();
	void Run(InputManager const& inputManager, Renderer& renderer);
	int GetSurvivalTime() const;
	int GetScore() const;

private:

	int _score{ 0 };
};

#endif