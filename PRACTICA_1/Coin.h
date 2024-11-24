#pragma once

#include "SceneObject.h"

class Coin : public SceneObject
{
public:

	Coin(Game* game, std::stringstream& atributos);

	~Coin();

	//void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	SDL_Rect getRect() const;

	bool isAlive() const;
};

