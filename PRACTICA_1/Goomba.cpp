#include "checkML.h"
#include "Goomba.h"
#include "Game.h"

using namespace std;

Goomba::Goomba(Game* game, istream& atributes) : Enemy(game, atributes)
	// position(), texture(game->getTexture(Game::GOOMBA)), gamePointer(game) , frame(0), frameRunner(0), previousOffset(0), frozen(true), velocity(2), ended(false), velocityGravity(8)
{

	texture = gamePointer->getTexture(Game::GOOMBA);

	//position = Vector2D<int>((posX) * Game::TILE_SIDE, (posY-1) * Game::TILE_SIDE);
	//direction = Vector2D<int>(-velocity, 0);
}

//void
//Goomba::render() const {
//
//	if (!frozen) {
//		//posición del goomba
//		SDL_Rect GPosition;
//		GPosition.x = position.getX();
//		GPosition.y = position.getY();
//		GPosition.w = Game::TILE_SIDE;
//		GPosition.h = Game::TILE_SIDE;
//
//		//Muerte del goomba en el hit con el frame 2
//
//		//Renderizamos con los parametros actualizados
//		texture->renderFrame(GPosition, 0, frame);
//	}
//}


void
Goomba::update() {

	//FUNCIONAL: Los goombas spawnean en su sitio cuando el jugador alcanza a verlos en la pantalla
	int mapOffset = gamePointer->getMapOffset();
	if (position.getX() < mapOffset + Game::WINDOW_WIDTH * Game::TILE_SIDE) {
		frozen = false;
	}

	if (!frozen && !ended) {
		//REVISAR
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
			cout << "Goomba: Me he morido por limite de mapa" << endl;
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

//Collision
//Goomba::hit(const SDL_Rect& rect, bool fromPlayer) {
//
//	if (fromPlayer) {
//		Collision colisionPlayer = { false,false,{0,0,0,0} };
//
//		// Creamos un rect del bloque para compararlo con el del jugador
//		SDL_Rect GoombaRect;
//		GoombaRect = getRect();
//
//		// Creamos un rect del player tomando de valor el que le llega como argumento
//		SDL_Rect playerRect;
//		playerRect = rect;
//
//		SDL_Rect intersection;
//		if (SDL_IntersectRect(&playerRect, &GoombaRect, &intersection)) {
//			colisionPlayer.collides = false;
//			colisionPlayer.intersection = intersection;
//			if (intersection.w > intersection.h) {
//				frame = 2; //Si da tiempo añadir un contador para que de tiempo a poner el frame de muerte un momento
//				ended = true;
//			}
//			else {
//				colisionPlayer.damages = true;
//			}
//
//			return colisionPlayer;
//		}
//		return colisionPlayer;
//	}
//	else {
//		return gamePointer->checkEnemyCollision(rect, fromPlayer);
//	}
// 
//}

//SDL_Rect
//Goomba::getRect() const {
//	SDL_Rect GoombaRect;
//	GoombaRect.x = position.getX() + gamePointer->getMapOffset();
//	GoombaRect.y = position.getY();
//	GoombaRect.w = Game::TILE_SIDE;
//	GoombaRect.h = Game::TILE_SIDE;
//	return GoombaRect;
//}

//bool
//Goomba::isAlive() const {
//	return !ended;
//}