#pragma once

#include <functional>
#include "GameState.h"
#include <vector>


class AnimationState : public GameState
{
protected:
	GameState* currentGameState;
	std::function<bool()> callback;

public:
	AnimationState( GameState* gameState, std::function<bool()> cb, Game* g);

	~AnimationState();

	void render() const override;

	void update() override;
};

