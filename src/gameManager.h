#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SDL.h"
#include <random>
#include <vector>
#include <memory>

#include "inputManager.h"
#include "renderer.h"
#include "player.h"

class GameManager {
public:
	GameManager();
	~GameManager();
	void Run(InputManager const* inputManager, Renderer* renderer);

	// Getters / Setters:

	int GetSurvivalTime() const;
	int GetScore() const;
private:
	/*
	std::random_device _randomDevice;
	std::mt19937 _randomEngine;
	*/

	std::unique_ptr<Player> _playerActor;

	int _score{ 0 };
};

#endif