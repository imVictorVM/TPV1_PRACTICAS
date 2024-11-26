#pragma once

#include "SceneObject.h"

class Game;

class Pickable : public SceneObject {
public:
	Pickable(Game* game);

	Pickable(Game* game, std::istream& atributes);

	~Pickable();

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	SDL_Rect getRect() const;

};