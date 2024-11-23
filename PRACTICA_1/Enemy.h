#pragma once

#include "Collision.h"
#include "SceneObject.h"

class Enemy : public SceneObject {
public:
	Collision hit(SDL_Rect& rect, bool fromPlayer) override;
};