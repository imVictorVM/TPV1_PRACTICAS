#pragma once

#include "Pickable.h"

class Game;
class PlayState;

class Mushroom : public Pickable
{

public:

	Mushroom(PlayState* game, SDL_Rect rect);

	~Mushroom();

	void update() override;

};