#include "checkML.h"
#include "Goomba.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

Goomba::Goomba(PlayState* gameState, istream& atributes) : Enemy(gameState, atributes)
{
	texture = gameState->getGame()->getTexture(Game::GOOMBA);
}

Goomba::~Goomba() {

}

void
Goomba::update() {

	//FUNCIONAL: Los goombas spawnean en su sitio cuando el jugador alcanza a verlos en la pantalla
	int mapOffset = playState->getMapOffset();
	if (position.getX() < mapOffset + PlayState::WINDOW_WIDTH * PlayState::TILE_SIDE) {
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
		Collision collision = playState->checkEnemyCollision(GoombaRect, false);
		
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
		
		collision = playState->checkEnemyCollision(GoombaRect, false);
		
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

		if (position.getX() < 0 - PlayState::TILE_SIDE || position.getY() >= 470) {
			ended = true;
			cout << "Goomba: Me he muerto por limite de mapa" << endl;
		}
	}

	//FUNCIONAL: Los goombas se mueven en funcion el offset del mapa y su posición
	int newOffset = playState->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}
}

