#include "checkML.h"

#include "SceneObject.h"
#include "Game.h"
using namespace std;

SceneObject::SceneObject(Game* g, Vector2D<int> pos, Vector2D<int> dir) : GameObject(g){
	position = pos;
	direction = dir;
	frame = 0;
	width = Game::TILE_SIDE;
	height = Game::TILE_SIDE;
	//rect = SDL_Rect(pos.getX(), pos.getY(),width,height);

	if (gamePointer->getMapOffset() + Game::WIN_WIDTH > pos.getX()) frozen = false;
	else frozen = true;

	
}
SceneObject::SceneObject(Game* g) : GameObject(g) {
	position =  Vector2D(0,0);
	direction = Vector2D(0,0);
	frame = 0;
	width = Game::TILE_SIDE;
	height = Game::TILE_SIDE;
	//rect = SDL_Rect(pos.getX(), pos.getY(), width, height);

	frozen = false;
	
}

SceneObject::~SceneObject() {
}

void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}
