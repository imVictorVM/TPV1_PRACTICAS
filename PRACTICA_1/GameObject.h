#pragma once
#include "gameList.h"

class Game;
class GameState;

class GameObject {
protected:
	GameState* gamePointer;
	GameList<GameObject>::anchor anc;
public:

	GameObject(GameState* g);
	virtual ~GameObject() = 0;
	virtual void render() const = 0;
	virtual void update() = 0;
	void setListAnchor(GameList<GameObject>::anchor&& setter);
	//Con esto hacemos la creacion y la destruccion de los objetos
};