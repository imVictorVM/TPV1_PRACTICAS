#include "checkML.h"
#include "Goomba.h"
#include "Game.h"

using namespace std;

Goomba::Goomba(Game* game, istream& atributes) : Enemy(game, atributes)
{
	texture = gamePointer->getTexture(Game::GOOMBA);
}

Goomba::~Goomba() {

}

void
Goomba::update() {

	//FUNCIONAL: Los goombas spawnean en su sitio cuando el jugador alcanza a verlos en la pantalla
	int mapOffset = gamePointer->getMapOffset();
	if (position.getX() < mapOffset + Game::WINDOW_WIDTH * Game::TILE_SIDE) {
		frozen = false;
	}

	if (!frozen && !ended) {

		Vector2D<int> newPosition = position + direction;

		//FUNCIONAL: Animacion del goomba para moverse cuando no esta congelado
		if (frameRunner == 0) frame = 0;
		if (frameRunner == 1) frame = 1;
		if (frameRunner > 1) frameRunner = 0;
		else frameRunner++;

		//INTENTO DE TRYTOMOVE, EXPLICADO EN EL INFO.TXT
		//Collision colision = tryToMove(direction,Collision::ENEMIES);

		SDL_Rect GoombaRect = getRect();
		GoombaRect.y += direction.getY();
		GoombaRect.x += direction.getX();
		
		// CAMBIAR: Verifica colisión en todas las direcciones
		Collision collision = gamePointer->checkEnemyCollision(GoombaRect, false);
		
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
		
		//RECALCULO DE LA COLISION
		GoombaRect.x += direction.getX();
		GoombaRect.y = position.getY();
		
		collision = gamePointer->checkEnemyCollision(GoombaRect, false);
		
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
			cout << "Goomba: Me he muerto por limite de mapa" << endl;
		}
	}

	//FUNCIONAL: Los goombas se mueven en funcion el offset del mapa y su posición
	int newOffset = gamePointer->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}
}

