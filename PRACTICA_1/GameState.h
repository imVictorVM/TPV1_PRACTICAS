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
	GameList<GameObject*>gameObjects;
	PlayState* game;
	std::list<EventHandler*> eventHandlers;
public:
	void update();
	void render() const;
	void handleEvent();

	void addEventListener();
	void addObject();
	void getGame() const;
};

