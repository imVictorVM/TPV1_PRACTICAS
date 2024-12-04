#pragma once

#include "gameList.h"
#include <list>
#include <SDL.h>

class Game;
class GameObject;
class EventHandler;

class GameState
{
private: 
	GameList<GameObject>gameObjects;
	Game* game;
	std::list<EventHandler*> eventHandlers;
public:
	GameState(Game* g);
	~GameState();
	void render() const;
	void update();
	void handleEvent(const SDL_Event& event);

	void addEventListener(EventHandler* e);
	void addObject(GameObject* g);
	Game* getGame() const;
};

