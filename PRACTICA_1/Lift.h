#pragma once

#include "SceneObject.h"

class Game;

class Lift : public SceneObject
{
public:
	Lift(Game* game, std::istream& atributos);

	~Lift();

	//void render() const override;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	//SDL_Rect getRect() const;
};

