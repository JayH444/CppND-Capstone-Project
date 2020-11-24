#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SDL.h"
#include "util.h"

#include "inputManager.h"
#include "renderer.h"
#include "player.h"
#include "gameObject.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	void Run(InputManager const* inputManager, Renderer* renderer);
	void InitializeGameObject(GameObject* g, std::string fileP, Vector2 texD, Vector2 colD, int x=0, int y=0);

	int RandInt(int min, int max);
	int RandFloat(float min, float max);

	// Getters / Setters:

	int GetSurvivalTime() const;
	int GetScore() const;

private:
	std::random_device _randomDevice;
	std::mt19937 _randomEngine;

	std::unique_ptr<Player> _playerActor;
	std::vector<std::unique_ptr<GameObject>> _objects;
	std::vector<std::string> _asteroidTextures;
	Renderer* _r;

	int _score{ 0 };
};

#endif