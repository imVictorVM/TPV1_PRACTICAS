#include "GameState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "EventHandler.h"
#include "GameObject.h"

GameState::GameState(Game* g) {
	game = g;
}

GameState::~GameState() {
	delete game;
}

void
GameState::render() const {
	for (const GameObject* gameObject : gameObjects) {
		gameObject->render();
	}
}

void
GameState::update() {
	for (GameObject* gameObject : gameObjects) {
		gameObject->update();
	}
}

void
GameState::handleEvent(const SDL_Event& event) {
	for (EventHandler* handler : eventHandlers) {
		handler->handleEvent(event);
	}
}

void
GameState::addEventListener(EventHandler* e) {
	eventHandlers.push_back(e);
}

void
GameState::addObject(GameObject* g) {
	gameObjects.push_back(g);
}

