#pragma once
#include "Vector2D.h"
#include "Game.h"
#include <sstream>

class Game;

class Block
{
public:
	enum Type
	{
		normal,
		surprise,
		empty,
		hidden
	};
	enum Action {
		powerup,
		coin
	};
private:
	Vector2D<int> position;
	Texture* TextureBlock;
	Type type;
	Action action;
	Game* game;
	int frameBlock;
	int previousOffset;
	bool object;
public:

	Block(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	SDL_Rect getRect() const;

	bool ObtainObject();
};

