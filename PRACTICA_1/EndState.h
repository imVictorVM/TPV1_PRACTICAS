#pragma once

#include "GameState.h"
#include "button.h"
#include "background.h"


class EndState : public GameState
{
private:
	Game* gamePointer;
	background* fondo;
	background* winLose;
	bool condition;
	
public:
	EndState(Game* game, bool WinLose);
	~EndState();
	void render();
};

