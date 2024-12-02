#pragma once

#include "Enemy.h"


class Game;
class PlayState;

class Koopa :public Enemy
{

public:

	Koopa(PlayState* game, std::istream& atributos);

	~Koopa();

	void render() const override;

	void update() override;

};