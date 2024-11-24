#pragma once

#include <SDL.h>

#include "GameObject.h"
#include "Vector2D.h"
#include "gameList.h"
#include "Collision.h"
#include "Texture.h"
#include "Game.h"

class SceneObject : public GameObject {
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	int width;
	int height;
	int frame;
	int frameRunner;
	bool frozen;
	int previousOffset;
	int velocity;
	bool ended;
	int velocityGravity;

	SDL_Rect rect;
	SDL_Renderer* renderer;
	GameList<SceneObject>::anchor anchor;

public:
	SceneObject(Game* g, Vector2D<int> pos, Vector2D<int> dir);
	SceneObject(Game* g);
	~SceneObject();

	virtual Collision hit(const SDL_Rect& rect, bool fromPlayer) = 0;

	void setListAnchor(GameList<SceneObject>::anchor&& anchor);

};