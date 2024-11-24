#pragma once

#include "SceneObject.h"

class Game;

class Lift : public SceneObject
{

	Texture* LiftTexture;

public:
	Lift(Game* game, std::stringstream& atributos);

	~Lift();

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	SDL_Rect getRect() const;
};

