#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Game;

class Mushroom
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Texture* mushroomTexture;
	Game* mushroomGame;

public:

	Mushroom(Game* game, int posX, int posY);

	void render() const;

	void update();

	bool hit() const;
};