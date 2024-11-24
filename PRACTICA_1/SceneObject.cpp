#include "checkML.h"

#include "SceneObject.h"

using namespace std;

SceneObject::SceneObject(Game* g, Vector2D<int> pos, Vector2D<int> dir) : GameObject(g){
	position = pos;
	direction = dir;
	frame = 0;
	rect = SDL_Rect(pos.getX(), pos.getY(), Game::TILE_SIDE, Game::TILE_SIDE);

	if (gamePointer->getMapOffset() + Game::WIN_WIDTH > pos.getX()) frozen = false;
	else frozen = true;

	
}
SceneObject::SceneObject(Game* g) : GameObject(g) {}

SceneObject::~SceneObject() {
}

void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}
