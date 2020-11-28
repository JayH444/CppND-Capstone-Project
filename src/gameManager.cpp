#include "gameManager.h"

GameManager::GameManager() : _r(nullptr), _randomEngine(_randomDevice()) {
}

GameManager::~GameManager() {
	// SDL_Texture can't be used with standard library smart pointers in an easy clean way, so they'll have to be 
	// dealt with as raw pointers.
	while (_r->_loadedTexturesHashMap.empty() == false) {
		std::string key = _r->_loadedTexturesKeys.back();
		SDL_Texture* i = _r->_loadedTexturesHashMap[key];
		std::cout << "Destroying texture " << key << " in _loadedTexturesHashMap...\n";
		if (i != nullptr) {
			SDL_DestroyTexture(i);
			i = nullptr;
			_r->_loadedTexturesHashMap.erase(key);
		}
		_r->_loadedTexturesKeys.pop_back();
	}
}

void GameManager::LoadAllGameTextures() {
	/*
	Credits to "Peter Parker" of stackoverflow for their implementation of using std::filesystem to find
	all the files in a directory.
	November 2020,
	https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
	*/

	// Load all the texture files in the "textures/" directory.
	std::string texturesPath = "textures/";
	for (const auto& entry : FS::directory_iterator(texturesPath)) {
		std::string filePath = entry.path().string();
		std::cout << "Loading " << filePath << "...\n";
		_r->LoadTexture(filePath);
		if (filePath.find("asteroid") != std::string::npos) {
			_asteroidTextures.emplace_back(filePath);
		}
	}
}

int GameManager::RandInt(int min, int max) {
	std::uniform_int_distribution random_int(min, max);
	return random_int(_randomEngine);
}

void GameManager::InitializeGameObject(GameObject* g, std::string fileP, int x, int y, int textureScaleMult, IntVector2 colD) {
	g->SetTexture(_r->_loadedTexturesHashMap[fileP]);
	IntVector2 texD = _r->_loadedTexturesDimensionsHashMap[fileP];
	texD._x *= 2;
	texD._y *= 2;
	if (colD._x == 0) {
		colD._x = texD._x;
		colD._y = texD._y;
	}
	g->SetTextureDimensions(texD._x, texD._y);
	g->SetCollisionDimensions(colD._x, colD._y);
	g->SetX(x);
	g->SetY(y);
}

void GameManager::InitializeAsteroid() {
	auto _asteroid = std::shared_ptr<GameObject>(new GameObject());

	// Pick a random asteroid texture and get its dimensions...
	std::string chosenTexture = _asteroidTextures[RandInt(0, _asteroidTextures.size() - 1)];
	//std::cout << "Random asteroid texture chosen is " << chosenTexture << "!\n";
	IntVector2 td = _r->_loadedTexturesDimensionsHashMap[chosenTexture];
	IntVector2 colD = IntVector2(td._x * 0.85, td._y * 0.85);

	InitializeGameObject(_asteroid.get(), chosenTexture, RandInt(0, SCREEN_WIDTH - td._x), -(RandInt(td._y * 2, td._y * 5)), 2, colD);
	_objects.emplace_back(std::move(_asteroid));
}

void GameManager::Run(InputManager const* inputManager, Renderer* renderer) {
	bool running = true;
	_r = renderer;
	LoadAllGameTextures();

	// Create the player:
	_playerActor = std::unique_ptr<Player>(new Player());
	int pX = SCREEN_WIDTH / 2 - 32;
	int pY = SCREEN_HEIGHT / 2 - 32;
	IntVector2 cD = IntVector2(28, 36);
	InitializeGameObject(_playerActor.get(), "textures/ship.bmp", pX, pY, 2, cD);

	int maxAsteroidNumber = 10;
	double asteroidIncrementTimer = 10.0;

	/*
	Credits to Brandon Foltz for their implementation of delta time, and "Patrick le Duc" of 
	stackexchange/stackoverflow for their version of it using SDL_GetPerformanceCounter().
	November 2020,
	https://carlopsite.files.wordpress.com/2017/08/the_game_loop_and_frame_rate_management.pdf
	https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl
	*/

	Uint64 frameTimeStart = 0;  // Time at the start of a frame.
	Uint64 frameTimeEnd = 0;  // Time at the end of a frame.
	double frameDeltaTime = 0;  // Time since start of frame.
	double deltaTimeSeconds = 0;
	// ALL game actions where applicible should be scaled by deltaTimeSeconds to ensure they're being executed at the 
	// same speed regardless of framerate.
	double totalTimeSeconds = 0;

	int targetFramerate = 300;
	int targetMsPerFrame = 1000 / targetFramerate;

	while (running) {

		frameTimeStart = SDL_GetPerformanceCounter();

		// Handle inputs:
		inputManager->HandleInput(running, _playerActor.get());

		// Update game state:
		deltaTimeSeconds = frameDeltaTime / 1000.0;
		totalTimeSeconds = (double)SDL_GetTicks() / 1000.0;

		if (_playerActor->GetIsAlive()) {
			_playerActor->Update(deltaTimeSeconds);

			// Dont run this until a brief startup grace period ends.
			if (totalTimeSeconds > 2) {
				asteroidIncrementTimer -= deltaTimeSeconds;

				// Handle spawning asteroids, cleanup, moving them, and checking collisions...
				for (int n = 0; n < _objects.size(); n++) {
					auto i = _objects[n];
					if (i->GetVelocityX() != 0 || i->GetVelocityY() != 0) {
						i->SetX(i->GetX() + i->GetVelocityX() * deltaTimeSeconds);
						i->SetY(i->GetY() + i->GetVelocityY() * deltaTimeSeconds);
					}
					if (i->GetVelocityY() == 0) {
						i->SetMovementY(RandInt(75, 300), 1);
					}
					if (i->CheckBoundingBoxCollision(_playerActor.get())) {
						std::cout << "Player is colliding with object " << n << "!\n";
						_playerActor->SetIsAlive(false);
					}
					if (i->GetY() > SCREEN_HEIGHT) {
						i->SetIsAlive(false);
					}
				}
				for (int n = 0; n < _objects.size(); n++) {
					auto i = _objects[n];
					if (i->GetIsAlive() == false) {
						_objects.erase(_objects.begin() + n);
						n--;
					}
				}
				if (_objects.size() < maxAsteroidNumber) {
					InitializeAsteroid();
				}
				SetScore(totalTimeSeconds - 2);
				if (asteroidIncrementTimer <= 0 && maxAsteroidNumber < 500) {
					maxAsteroidNumber++;
					std::cout << "Incremented asteroid number to " << maxAsteroidNumber << "\n";
					asteroidIncrementTimer = 10.0;
				}
			}
		}

		// Render:
		renderer->Render(_playerActor.get(), &_objects);

		// Calculate delta time:
		frameTimeEnd = SDL_GetPerformanceCounter();
		frameDeltaTime = (double)(frameTimeEnd - frameTimeStart) * 1000.0 / (double)SDL_GetPerformanceFrequency();

		if (frameDeltaTime < 1 || frameDeltaTime > 1000) {
			frameTimeStart = SDL_GetPerformanceCounter();
			SDL_Delay(targetMsPerFrame);
			frameTimeEnd = SDL_GetPerformanceCounter();
			frameDeltaTime = (double)(frameTimeEnd - frameTimeStart) * 1000.0 / (double)SDL_GetPerformanceFrequency();
		}
		if (frameDeltaTime > 1) {
			renderer->UpdateWindowTitle(1000 / (int)frameDeltaTime, GetScore());
		}
		else {
			renderer->UpdateWindowTitle("Tyrianoid - FPS: 1000+", GetScore());
		}
	}
}