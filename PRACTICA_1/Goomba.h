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
	Texture* goombaTexture;
	Game* game;
	int frame;
	int frameRunner;
	bool frozen;
	int previousOffset;

public:

	Goomba(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);
};