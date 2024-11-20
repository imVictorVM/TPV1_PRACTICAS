#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"

class Game;

class Goomba
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Vector2D<int> notGround;
	Texture* goombaTexture;
	Game* game;
	int frame;
	int frameRunner;
	bool frozen;
	int previousOffset;
	int velocity;
	bool ended;
public:

	Goomba(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	SDL_Rect getRect() const;
};