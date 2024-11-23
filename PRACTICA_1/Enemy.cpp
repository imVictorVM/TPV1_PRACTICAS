#include "checkML.h"
#include "Enemy.h"

Collision
Enemy::hit(const SDL_Rect& rect, bool fromPlayer) {

	if (fromPlayer) {
		Collision colisionPlayer = { false,false,{0,0,0,0} };

		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect GoombaRect;
		GoombaRect.x = position.getX() + game->getMapOffset();
		GoombaRect.y = position.getY();
		GoombaRect.w = Game::TILE_SIDE;
		GoombaRect.h = Game::TILE_SIDE;

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &GoombaRect, &intersection)) {
			colisionPlayer.collides = false;
			colisionPlayer.damages = true;
			colisionPlayer.intersection = intersection;
			if (colisionPlayer.intersection.y < position.getY() + Game::TILE_SIDE / 2) frame = 2;
			return colisionPlayer;
		}
		return colisionPlayer;
	}

}