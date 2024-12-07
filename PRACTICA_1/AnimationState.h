#pragma once

#include <functional>
#include "GameState.h"



class AnimationState : public GameState
{
protected:
	GameState* currentGameState;
	std::function<bool()> callback;

public:
	AnimationState(GameState* gameState, std::function<bool()> cb, Game* g);

	~AnimationState();

	void render() const;

	void update();
};

