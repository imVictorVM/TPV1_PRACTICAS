#pragma once

#include "GameState.h"
#include "button.h"
#include "background.h"
#include <vector>
#include <memory>

class PlayState;

class PauseState : public GameState
{
private:
	Game* gamePointer;
	PlayState* playState;
public:
	PauseState(Game* game, PlayState* pS);
	~PauseState();
	void render() const override;
	void update() override;
};

