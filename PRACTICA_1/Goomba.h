#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Game;

class Goomba
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Texture* goombaTexture;
	Game* goombaGame;
	int frameRunner;
	bool frozen;

public:

	Goomba(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	bool hit() const;
};