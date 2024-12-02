#pragma once

#include "Enemy.h"


class Game;
class PlayState;

class Goomba :public Enemy
{

public:

	Goomba(PlayState* game, std::istream& atributos);

	~Goomba();

	void update() override;

};