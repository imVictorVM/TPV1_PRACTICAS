#include "GameState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"

//VIRTUALES
//GameState::~GameState() {
//	gameObject.clear();
//}

//VIRTUALES
//void
//GameState::handleEvent(const SDL_Event& event) {
//	for (EventHandler* handler : eventHandlers) {
//		handler->handleEvent(event);
//	}
//}

void
GameState::addEventListener(EventHandler* e) {
	eventHandlers.push_back(e);
}

void
GameState::addObject(GameObject* g) {
	gameObjects.push_back(g);
}

