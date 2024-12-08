#pragma once

#include "GameState.h"
#include "button.h"
#include "background.h"


class EndState : public GameState
{
private:
	Game* gamePointer;
	background* fondo;
	background* gameOver;
	
public:
	EndState(Game* game);
	~EndState();
	void render();
};

