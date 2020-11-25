#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "util.h"
#include "gameObject.h"

class Player : public GameObject {
public:
	Player();
	//~Player();

	void Update(double deltaTimeSeconds);
	bool HasMovementInput() { return _inputX || _inputY; }

	// Getters / Setters:

	char GetInputX() { return _inputX; }
	char GetInputY() { return _inputY; }
	//
	void SetX(float x) override;
	void SetY(float y) override;
	void SetMovementDirection(const Uint8* keystate);


	const int _moveSpeed;

private:
	char _inputX;
	char _inputY;
};

#endif