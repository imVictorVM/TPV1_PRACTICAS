#pragma once

#include "GameState.h"
#include "button.h"
#include "background.h"
#include <vector>
#include <memory>

class PauseState : public GameState
{
private:
	Game* gamePointer;
	//background* fondo;
public:
	PauseState(Game* game);
	~PauseState();
};

