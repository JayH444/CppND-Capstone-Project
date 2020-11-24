#include "gameManager.h"

GameManager::GameManager() : _r(nullptr), _randomEngine(_randomDevice()) {
}

GameManager::~GameManager() {
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

void GameManager::InitializeGameObject(GameObject* g, std::string fileP, Vector2 texD, Vector2 colD, int x, int y) {
	g->SetTextureDimensions(texD._x, texD._y);
	g->SetCollisionDimensions(colD._x, colD._y);
	_r->LoadTextureForGameObject(g, fileP);
	g->SetX(x);
	g->SetY(y);
}

void GameManager::Run(InputManager const* inputManager, Renderer* renderer) {
	bool running = true;
	_r = renderer;

	// Create the player:
	_playerActor = std::unique_ptr<Player>(new Player());
	int pX = SCREEN_WIDTH / 2 - 32;
	int pY = SCREEN_HEIGHT / 2 - 32;
	InitializeGameObject(_playerActor.get(), "textures/ship.bmp", Vector2(64, 64), Vector2(44, 48), pX, pY);
	
	/*
	Credits to Peter Parker of stackoverflow for their implementation of using std::filesystem to find
	all the files in a directory.
	November 2020,
	https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
	*/

	std::string texturesPath = "textures/";
	for (const auto& entry : FS::directory_iterator(texturesPath)) {
		std::string filePath = entry.path().string();
		std::cout << "Loading " << filePath << "...\n";
		_r->LoadTexture(filePath);
		if (filePath.find("asteroid") != std::string::npos) {
			std::cout << "Found asteroid texture " << filePath << "!\n";
			_asteroidTextures.emplace_back(filePath);
		}
	}

	for (int i = 0; i < 5; i++) {
		auto _asteroid = std::unique_ptr<GameObject>(new GameObject());

		//InitializeGameObject(_asteroid.get(),
	}
	//_objects.emplace_back()

	/*
	Credits to Brandon Foltz for their implementation of delta time, and Patrick le Duc of 
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

	int targetFramerate = 300;
	int targetMsPerFrame = 1000 / targetFramerate;

	while (running) {

		frameTimeStart = SDL_GetPerformanceCounter();


		// Handle inputs:
		inputManager->HandleInput(running, _playerActor.get());

		// Update game state:
		deltaTimeSeconds = frameDeltaTime / 1000.0;

		if (abs(_playerActor->GetVelocityX()) > 0 || abs(_playerActor->GetVelocityY()) > 0) {
			_playerActor->SetX(_playerActor->GetX() + _playerActor->GetVelocityX() * deltaTimeSeconds);
			_playerActor->SetY(_playerActor->GetY() + _playerActor->GetVelocityY() * deltaTimeSeconds);
		}

		if (_playerActor->HasMovementInput()) {

			// Calculate the X and Y component for all directions of movement, including diagonal:
			float changeX = 0;
			float changeY = 0;
			if (_playerActor->HasMovementInput()) {
				float angle = SDL_atan2f(_playerActor->GetInputX(), _playerActor->GetInputY());
				changeX = SDL_cosf(angle);
				changeY = SDL_sinf(angle);
			}

			_playerActor->SetMovementX(changeX * (float)_playerActor->_moveSpeed, 1);
			_playerActor->SetMovementY(changeY * (float)_playerActor->_moveSpeed, 1);
		}
		else {
			_playerActor->DecayVelocity(deltaTimeSeconds);
		}


		// Render:
		renderer->Render(_playerActor.get());


		frameTimeEnd = SDL_GetPerformanceCounter();
		frameDeltaTime = (double)(frameTimeEnd - frameTimeStart) * 1000.0 / (double)SDL_GetPerformanceFrequency();

		if (frameDeltaTime < 1 || frameDeltaTime > 1000) {
			frameTimeStart = SDL_GetPerformanceCounter();
			SDL_Delay(targetMsPerFrame);
			frameTimeEnd = SDL_GetPerformanceCounter();
			frameDeltaTime = (double)(frameTimeEnd - frameTimeStart) * 1000.0 / (double)SDL_GetPerformanceFrequency();
			renderer->UpdateWindowTitle(1000 / (int)frameDeltaTime);
		}
	}
}