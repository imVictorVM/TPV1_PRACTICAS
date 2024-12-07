#include "AnimationState.h"

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
	callback;
}