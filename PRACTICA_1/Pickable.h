#pragma once

#include "SceneObject.h"

class Game;
class PlayState;

class Pickable : public SceneObject {
public:
	Pickable(PlayState* game);

	Pickable(PlayState* game, std::istream& atributes);

	~Pickable();

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	SDL_Rect getRect() const;

};