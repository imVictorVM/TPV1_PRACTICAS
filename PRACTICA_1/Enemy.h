#pragma once

#include "SceneObject.h"

class Game;
class PlayState;

class Enemy : public SceneObject {
public:
	Enemy(PlayState* game, std::istream& atributes);

	~Enemy();

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	SDL_Rect getRect() const;
};