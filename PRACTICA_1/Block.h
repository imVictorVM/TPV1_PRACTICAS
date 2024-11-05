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
public:

	Block(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);
	bool hit(Vector2D<int> playerPosition);

	SDL_Rect getRect() const;
};

