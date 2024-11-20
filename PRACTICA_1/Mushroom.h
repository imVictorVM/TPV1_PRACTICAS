#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"

class Game;

class Mushroom
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Texture* mushroomTexture;
	Game* mushroomGame;
	int velocity;

public:

	Mushroom(Game* game, int posX, int posY);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

};