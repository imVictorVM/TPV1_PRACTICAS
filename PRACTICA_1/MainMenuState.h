#pragma once

#include "GameState.h"
#include "button.h"
#include <vector>
#include <memory>

//class button;

class MainMenuState : public GameState
{
private:
	std::vector<std::unique_ptr<button>> MenuButtons;
	Game* gamePointer;
public:
	MainMenuState(Game* game);
	void update();
	void render() const;
	void handleEvent(const SDL_Event& event);
};

