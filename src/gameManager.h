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
	void InitializeGameObject(GameObject* g, std::string fileP, int x=0, int y=0, int textureScaleMult=2, IntVector2 colD=IntVector2(0, 0));
	void LoadAllGameTextures();

	int RandInt(int min, int max);
	int RandFloat(float min, float max);

	// Getters / Setters:

	int GetSurvivalTime() const;
	int GetScore() const;

private:
	std::random_device _randomDevice;
	std::mt19937 _randomEngine;

	std::unique_ptr<Player> _playerActor;
	std::vector<std::shared_ptr<GameObject>> _objects;
	//std::unordered_map<
	std::vector<std::string> _asteroidTextures;
	Renderer* _r;

	int _score{ 0 };
};

#endif