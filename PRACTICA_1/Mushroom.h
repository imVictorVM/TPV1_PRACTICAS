#pragma once

#include "Pickable.h"

class Game;

class Mushroom : public Pickable
{

public:

	Mushroom(Game* game, SDL_Rect rect);

	~Mushroom();

	void update() override;

};