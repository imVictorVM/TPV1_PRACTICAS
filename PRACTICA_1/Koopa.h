#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"

class Game;

class Koopa
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Texture* koopaTexture;
	Game* koopaGame;
	int frameRunner;
	bool frozen;

public:

	Koopa(Game* game, std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);
};