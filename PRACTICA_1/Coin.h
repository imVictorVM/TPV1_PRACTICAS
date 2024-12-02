#pragma once

#include "Pickable.h"

class Coin : public Pickable
{
public:

	Coin(PlayState* game, std::istream& atributos);

	~Coin();

	void update() override;

};

