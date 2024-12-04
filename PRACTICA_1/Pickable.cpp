#include "checkML.h"
#include "Pickable.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

Pickable::Pickable(PlayState* game) : SceneObject(game) {

}

Pickable::Pickable(PlayState* game, istream& atributes) : SceneObject(game, atributes) {

}

Pickable::~Pickable() {

}

Collision
Pickable::hit(const SDL_Rect& rect, bool fromPlayer) {

	Collision colisionPlayer = { false,false,{0,0,0,0} };
	if (fromPlayer) {
		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect KoopaRect;
		KoopaRect = getRect();

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &KoopaRect, &intersection)) {
			colisionPlayer.collides = true;
			colisionPlayer.intersection = intersection;
			ended = true;
			return colisionPlayer;
		}
		return colisionPlayer;
	}
	return colisionPlayer;

}

SDL_Rect
Pickable::getRect() const {
	SDL_Rect CPosition;
	CPosition.x = position.getX() + playState->getMapOffset();
	CPosition.y = position.getY();
	CPosition.w = PlayState::TILE_SIDE;
	CPosition.h = PlayState::TILE_SIDE;
	return CPosition;
}
