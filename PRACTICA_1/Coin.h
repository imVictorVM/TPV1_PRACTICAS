#pragma once

#include "Pickable.h"

class Coin : public Pickable
{
public:

	Coin(Game* game, std::istream& atributos);

	~Coin();

	//void render() const;

	void update();

	//Collision hit(const SDL_Rect& rect, bool fromPlayer);

	//SDL_Rect getRect() const;

	//bool isAlive() const;
};

