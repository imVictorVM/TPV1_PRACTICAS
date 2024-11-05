#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Game;

class Koopa
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Texture* koopaTexture;
	Game* koopaGame;
	int frameRunner;

public:

	Koopa(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	bool hit() const;
};