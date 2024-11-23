#include "checkML.h"

#include "SceneObject.h"

using namespace std;

SceneObject::SceneObject(Game* g, Vector2D<int> pos, Vector2D<int> dir, Texture* tex) : GameObject(g){
	position = pos;
	direction = dir;
	texture = tex;
	frame = 0;
	rect = SDL_Rect(pos.getX(), pos.getY(), Game::TILE_SIDE, Game::TILE_SIDE);

	if (game->getMapOffset() + Game::WIN_WIDTH > pos.getX()) frozen = false;
	else frozen = true;

	
}

void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}