#pragma once

#include "Enemy.h"


class Game;

class Goomba :public Enemy
{

public:

	Goomba(Game* game, std::istream& atributos);

	~Goomba();

	void update() override;

};