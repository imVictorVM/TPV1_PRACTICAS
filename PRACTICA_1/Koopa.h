#pragma once

#include "Enemy.h"


class Game;

class Koopa :public Enemy
{

public:

	Koopa(Game* game, std::istream& atributos);

	~Koopa();

	void render() const override;

	void update() override;

};