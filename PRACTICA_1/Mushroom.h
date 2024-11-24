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
	int previousOffset;
	bool ended;
	int velocityGravity;
public:

	Mushroom(Game* game, SDL_Rect rect);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	SDL_Rect getRect() const;

	bool isAlive() const;
};