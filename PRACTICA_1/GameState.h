#pragma once

#include "gameList.h"
#include <list>

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
	void update();
	void render() const;
	void handleEvent();

	void addEventListener();
	void addObject();
	void getGame() const;
};

