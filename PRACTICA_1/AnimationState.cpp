#include "checkML.h"
#include "AnimationState.h"
#include "Game.h"

AnimationState::AnimationState(GameState* gameState, std::function<bool()> cb, Game* g) : GameState(g){
	currentGameState = gameState;
	callback = cb;
}

AnimationState::~AnimationState() {

}

void AnimationState::render() const {
	currentGameState->render();
}

void AnimationState::update() {
	if (!callback()) {
		currentGameState->getGame()->popCurrentState();
	}
}