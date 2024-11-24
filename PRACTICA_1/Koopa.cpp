#include "checkML.h"
#include "Koopa.h"
#include "Game.h"

using namespace std;

Koopa::Koopa(Game* game, stringstream& atributes) :Enemy(game)
//position(), texture(game->getTexture(Game::KOOPA)), gamePointer(game), frame(0), frameRunner(0), frozen(true), previousOffset(0), velocity(2), ended(false), velocityGravity(8)
{
	string line;

	getline(atributes, line);

	stringstream lineStream(line);

	int posX, posY;
	lineStream >> posX;
	lineStream >> posY;

	texture = gamePointer->getTexture(Game::KOOPA);

	position = Vector2D<int>((posX) * Game::TILE_SIDE, (posY)* Game::TILE_SIDE);
	direction = Vector2D<int>(-velocity, 0);
	width = Game::TILE_SIDE * 2;
	height = Game::TILE_SIDE * 4;

}

//void
//Koopa::render() const {
//
//	if (!frozen) {
//		//posición del koopa
//		SDL_Rect KPosition;
//		KPosition.x = position.getX();
//		KPosition.y = position.getY() - Game::TILE_SIDE;
//		KPosition.w = Game::TILE_SIDE;
//		KPosition.h = Game::TILE_SIDE * 2; //Tiene dos tiles de altura
//		//IMPORTANTE APLICAR ESTO A MARIO GRANDE CUANDO TENGAMOS LA SETA
//
//		int frame = 0;
//		//movimiento del koopa, usando solo los dos primeros frames
//		if (frameRunner == 0) frame = 0;
//		if (frameRunner == 1) frame = 0;
//		if (frameRunner == 2) frame = 1;
//		if (frameRunner == 3) frame = 1;
//
//
//		//Renderizamos con los parametros actualizados
//		texture->renderFrame(KPosition, 0, frame);
//	}
//}


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
			cout << "Koopa: Me he morido por limite de mapa" << endl;
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

//Collision
//Koopa::hit(const SDL_Rect& rect, bool fromPlayer) {
//
//	Collision colisionPlayer = { false,false,{0,0,0,0} };
//
//	if (fromPlayer) {
//		// Creamos un rect del bloque para compararlo con el del jugador
//		SDL_Rect KoopaRect;
//		KoopaRect = getRect();
//
//		// Creamos un rect del player tomando de valor el que le llega como argumento
//		SDL_Rect playerRect;
//		playerRect = rect;
//
//		SDL_Rect intersection;
//		if (SDL_IntersectRect(&playerRect, &KoopaRect, &intersection)) {
//			colisionPlayer.collides = false;
//			colisionPlayer.intersection = intersection;
//			if (intersection.w > intersection.h) {
//				//frame = 2; Si da tiempo cambiarlo a una imagen de shell
//				ended = true;
//			}
//			else {
//				colisionPlayer.damages = true;
//			}
//			return colisionPlayer;
//		}
//		return colisionPlayer;
//	}
//	//else {
//	//	return game->checkPlayerCollision(rect, fromPlayer);
//	//}
//	return colisionPlayer;
//
//}

//SDL_Rect
//Koopa::getRect() const {
//	SDL_Rect KoopaRect;
//	KoopaRect.x = position.getX() + gamePointer->getMapOffset();
//	KoopaRect.y = position.getY();
//	KoopaRect.w = Game::TILE_SIDE;
//	KoopaRect.h = Game::TILE_SIDE;
//	return KoopaRect;
//}

bool 
Koopa::isAlive() const {
	return !ended;
}