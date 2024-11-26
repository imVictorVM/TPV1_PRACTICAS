#include "checkML.h"
#include "Koopa.h"
#include "Game.h"

using namespace std;

Koopa::Koopa(Game* game, istream& atributes) :Enemy(game, atributes)
{

	texture = gamePointer->getTexture(Game::KOOPA);
	width = Game::TILE_SIDE * 2;
	height = Game::TILE_SIDE * 4;

}

Koopa::~Koopa() {

}

void
Koopa::render() const {

	if (!frozen) {
		//posición del koopa
		SDL_Rect KPosition;
		KPosition.x = position.getX();
		KPosition.y = position.getY() - Game::TILE_SIDE;
		KPosition.w = Game::TILE_SIDE;
		KPosition.h = Game::TILE_SIDE * 2; //Tiene dos tiles de altura
		//IMPORTANTE APLICAR ESTO A MARIO GRANDE CUANDO TENGAMOS LA SETA

		int frame = 0;
		//movimiento del koopa, usando solo los dos primeros frames
		if (frameRunner == 0) frame = 0;
		if (frameRunner == 1) frame = 0;
		if (frameRunner == 2) frame = 1;
		if (frameRunner == 3) frame = 1;


		//Renderizamos con los parametros actualizados
		texture->renderFrame(KPosition, 0, frame);
	}
}


void
Koopa::update() {

	//FUNCIONAL: Los goombas spawnean en su sitio cuando el jugador alcanza a verlos en la pantalla
	int mapOffset = gamePointer->getMapOffset();
	if (position.getX() < mapOffset + Game::WINDOW_WIDTH * Game::TILE_SIDE) {
		frozen = false;
	}

	if (!frozen && !ended) {
		//REVISAR
		Vector2D<int> newPosition = position + direction;

		//FUNCIONAL: Animacion del koopa para moverse cuando no esta congelado
		if (frameRunner == 0 || frameRunner == 1) frame = 0;
		if (frameRunner == 2 || frameRunner == 3) frame = 1;
		if (frameRunner > 3) frameRunner = 0;
		else frameRunner++;
		frameRunner++;

		SDL_Rect KoopaRect = getRect();
		KoopaRect.y += direction.getY();
		KoopaRect.x += direction.getX();

		// CAMBIAR: Verifica colisión en todas las direcciones
		Collision collision = gamePointer->checkEnemyCollision(KoopaRect, false);

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
		KoopaRect.x += direction.getX();
		KoopaRect.y = position.getY();

		collision = gamePointer->checkEnemyCollision(KoopaRect, false);

		//COLISION HORIZONTAL
		if (!collision.collides) {
			position.setX(newPosition.getX());
		}
		else {
			if (collision.intersection.x > position.getX()) {
				direction.setX(-direction.getX());
			}
			else if (collision.intersection.x < position.getX()) {
				direction.setX(-velocity);
			}
		}

		if (position.getX() < 0 - Game::TILE_SIDE || position.getY() >= 470) {
			ended = true;
			cout << "Koopa: Me he muerto por limite de mapa" << endl;
		}
	}

	//FUNCIONAL: Los koopas se mueven en funcion el offset del mapa
	int newOffset = gamePointer->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position = Vector2D<int>(position.getX() - offsetChange, position.getY());
		previousOffset = newOffset;
	}
}
