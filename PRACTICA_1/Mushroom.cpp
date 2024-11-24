#include "checkML.h"
#include "Mushroom.h"
#include "Player.h"
#include "Game.h"

using namespace std;

Mushroom::Mushroom(Game* game, SDL_Rect rect) : position(), direction(), mushroomTexture(game->getTexture(Game::MUSHROOM)), mushroomGame(game), velocity(2), previousOffset(0), ended(false), velocityGravity(8)
{
	//posicion de la seta
	int posX = rect.x + mushroomGame->getMapOffset();
	int posY = rect.y - Game::TILE_SIDE;
	position = Vector2D<int>(posX, posY);
	direction = Vector2D<int>(velocity, 0);
}

void
Mushroom::render() const {
		//posición de la seta
		SDL_Rect MushPosition;
		MushPosition.x = position.getX();
		MushPosition.y = position.getY();
		MushPosition.w = Game::TILE_SIDE;
		MushPosition.h = Game::TILE_SIDE;

		//Renderizamos con los parametros actualizados
		mushroomTexture->renderFrame(MushPosition, 0, 0);
}


void
Mushroom::update() {

	if (!ended) {
		Vector2D<int> newPosition = position + direction;

		SDL_Rect MushRect = getRect();
		MushRect.y += direction.getY();
		MushRect.x += direction.getX();

		Collision collision = mushroomGame->checkEnemyCollision(MushRect, false);

		//COLISION VERTICAL
		if (!collision.collides) {
			direction.setY(velocityGravity);
			position.setY(newPosition.getY());
		}
		else {
			if (collision.intersection.y > position.getY()) {
				direction.setY(0);
			} //SUELO
			else if (collision.intersection.y < position.getY()) {
				direction.setY(velocityGravity);
			} //TECHO
		}

		MushRect.x += direction.getX();
		MushRect.y = position.getY();

		collision = mushroomGame->checkEnemyCollision(MushRect, false);

		//COLISION HORIZONTAL
		if (!collision.collides) {
			position.setX(newPosition.getX());
		}
		else {
			if (collision.intersection.x > position.getX()) {
				direction.setX(-direction.getX());
			}
			else if (collision.intersection.x < position.getX()) {
				direction.setX(-direction.getX());
			}
		}

		if (position.getX() < 0 - Game::TILE_SIDE || position.getY() >= 470) {
			ended = true;
			cout << "Seta: Me he morido por limite de mapa" << endl;
		}
	}

	//Los bloques se mueven en funcion el offset del mapa
	int newOffset = mushroomGame->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}

}


Collision
Mushroom::hit(const SDL_Rect& rect, bool fromPlayer) {
	Collision colision = { false,false,{0,0,0,0} };

	if (fromPlayer) {
		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect MushRect;
		MushRect = getRect();

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &MushRect, &intersection)) {
			colision.collides = true;
			colision.intersection = intersection;
			ended = true;
			return colision;
		}
		return colision;
	}
	return colision;
}

SDL_Rect
Mushroom::getRect() const {
	SDL_Rect MushRect;
	MushRect.x = position.getX() + mushroomGame->getMapOffset();
	MushRect.y = position.getY();
	MushRect.w = Game::TILE_SIDE;
	MushRect.h = Game::TILE_SIDE;
	return MushRect;
}

bool 
Mushroom::isAlive() const {
	return !ended;
}