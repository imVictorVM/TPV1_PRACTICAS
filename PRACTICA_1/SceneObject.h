#pragma once

#include <SDL.h>

#include "GameObject.h"
#include "Vector2D.h"
#include "gameList.h"
#include "Collision.h"
#include "Texture.h"

class Game;

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

	Texture* texture;


	SDL_Rect rect;
	SDL_Renderer* renderer;
	GameList<SceneObject>::anchor anchor;


public:
	SceneObject(Game* g);

protected:
	Collision tryToMove(const Vector2D<int>& speed, Collision::Target attack);

public:
	~SceneObject();

	void render() const override;

	virtual Collision hit(const SDL_Rect& rect, bool fromPlayer) = 0;

	void setListAnchor(GameList<SceneObject>::anchor&& anchor);

};