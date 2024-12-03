#pragma once

#include "gameList.h"
#include <list>

class Game;
class GameObject;
class EventHandler;
class PlayState;
//class PauseState;
//class MainMenuState;

class GameState
{
private: 
	GameList<GameObject>gameObjects;
	Game* game;
	std::list<EventHandler*> eventHandlers;
public:
	virtual ~GameState();
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void handleEvent(const SDL_Event& event);

	void addEventListener(EventHandler* e);
	void addObject(GameObject* g);
};

