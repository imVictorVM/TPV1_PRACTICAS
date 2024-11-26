#include "checkML.h"
#include "Enemy.h"
#include "Game.h"

using namespace std;

Enemy::Enemy(Game* game, istream& atributes) : SceneObject(game, atributes) {
	//direction = Vector2D<int>(-velocity, 0);
}

Collision
Enemy::hit(const SDL_Rect& rect, bool fromPlayer) {

	if (fromPlayer) {
		Collision colisionPlayer = { false,false,{0,0,0,0} };

		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect GoombaRect;
		GoombaRect = getRect();

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &GoombaRect, &intersection)) {
			colisionPlayer.collides = false;
			colisionPlayer.intersection = intersection;
			if (intersection.w > intersection.h) {
				frame = 2; //Si da tiempo añadir un contador para que de tiempo a poner el frame de muerte un momento
				ended = true;
			}
			else {
				colisionPlayer.damages = true;
			}

			return colisionPlayer;
		}
		return colisionPlayer;
	}
	else {
		return gamePointer->checkEnemyCollision(rect, fromPlayer);
	}

}

SDL_Rect
Enemy::getRect() const {
	SDL_Rect GoombaRect;
	GoombaRect.x = position.getX() + gamePointer->getMapOffset();
	GoombaRect.y = position.getY();
	GoombaRect.w = Game::TILE_SIDE;
	GoombaRect.h = Game::TILE_SIDE;
	return GoombaRect;
}