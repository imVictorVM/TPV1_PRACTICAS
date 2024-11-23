#pragma once

#include <SDL.h>

#include "GameObject.h"
#include "Vector2D.h"
#include "gameList.h"
#include "Collision.h"
#include "Texture.h"

using Game;

class SceneObject : public GameObject {
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	int width;
	int height;
	Texture* texture;

	GameList<SceneObject>::anchor anchor;

public:
	SceneObject(Game* g, Vector2D<int> pos, Vector2D<int> dir, Texture *tex);

	virtual Collision hit(SDL_Rect& rect, bool fromPlayer) = 0;

	void setListAnchor(GameList<SceneObject>::anchor&& anchor);

	void render() const override;
};