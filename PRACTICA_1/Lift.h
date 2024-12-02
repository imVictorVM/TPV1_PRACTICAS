#pragma once

#include "SceneObject.h"

class Game;
class PlayState;

class Lift : public SceneObject
{
public:
	Lift(PlayState* game, std::istream& atributos);

	~Lift();

	void update() override;

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

};

