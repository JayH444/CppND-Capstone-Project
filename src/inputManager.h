#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "util.h"
#include "player.h"

class InputManager {
public:
	void HandleInput(bool& running, Player* player) const;
};

#endif