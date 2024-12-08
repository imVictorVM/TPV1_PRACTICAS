#pragma once

#include "GameState.h"
#include "button.h"
#include "background.h"
#include <vector>
#include <memory>

//class button;

class MainMenuState : public GameState
{
private:
	Game* gamePointer;
	background* fondo;
public:
	MainMenuState(Game* game);
	~MainMenuState();
	//void update();
	//void render() const;
	//void handleEvent(const SDL_Event& event);
};

