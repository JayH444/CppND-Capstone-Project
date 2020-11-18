#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"

class GameManager {
public:
	GameManager();
	void Run(Controller const& controller, Renderer& renderer);
	int GetSurvivalTime() const;
	int GetScore() const;

private:

	int _score{ 0 };
};