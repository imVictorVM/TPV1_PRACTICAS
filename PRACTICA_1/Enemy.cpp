#include "checkML.h"
#include "Enemy.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

Enemy::Enemy(PlayState* game, istream& atributes) : SceneObject(game, atributes) {

}

Enemy::~Enemy() {

}

Collision
Enemy::hit(const SDL_Rect& rect, bool fromPlayer) {

	if (fromPlayer) {
		Collision colisionPlayer = { false,false,{0,0,0,0} };

		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect EnemyRect;
		EnemyRect = getRect();

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &EnemyRect, &intersection)) {
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
		return playState->checkEnemyCollision(rect, fromPlayer);
	}

}

SDL_Rect
Enemy::getRect() const {
	SDL_Rect EnemyRect;
	EnemyRect.x = position.getX() + playState->getMapOffset();
	EnemyRect.y = position.getY();
	EnemyRect.w = PlayState::TILE_SIDE;
	EnemyRect.h = PlayState::TILE_SIDE;
	return EnemyRect;
}