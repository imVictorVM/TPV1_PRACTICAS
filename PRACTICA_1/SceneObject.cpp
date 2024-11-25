#include "checkML.h"

#include "SceneObject.h"

#include "Game.h"

using namespace std;


SceneObject::SceneObject(Game* g) : GameObject(g) {
	position =  Vector2D(0,0);
	direction = Vector2D(0,0);
	frame = 0;
	frameRunner = 0;
	previousOffset = 0;
	velocity = 2;
	velocityGravity = 8;
	width = Game::TILE_SIDE;
	height = Game::TILE_SIDE;
	//rect = SDL_Rect(position.getX(), position.getY(), width, height);

	frozen = true;
	ended = false;
	
}

SceneObject::~SceneObject() {
	//delete texture;
	//GameObject::~GameObject();
}

void
SceneObject::render() const {

	if (!ended && !frozen) {
		SDL_Rect BPosition;
		BPosition.x = position.getX();
		BPosition.y = position.getY();
		BPosition.w = width;
		BPosition.h = height;

		texture->renderFrame(BPosition, 0, frame);
	}

}

SDL_Rect
SceneObject::getRect() const {
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = width;
	rect.h = height;
	return rect;
}

bool
SceneObject::isAlive() const {
	return !ended;
}


void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}
