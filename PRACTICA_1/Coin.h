#pragma once

#include "Pickable.h"

class Coin : public Pickable
{
public:

	Coin(Game* game, std::istream& atributos);

	~Coin();

	void update() override;

};

