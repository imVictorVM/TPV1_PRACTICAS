#pragma once

#include "SceneObject.h"

class Game;

class Enemy : public SceneObject {
public:
	Enemy(Game* game, std::istream& atributes);

	~Enemy();

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	SDL_Rect getRect() const;
};