#include "checkML.h"
#include "Goomba.h"
#include "Game.h"

using namespace std;

Goomba::Goomba(Game* game, stringstream& atributes) : position(), goombaTexture(game->getTexture(Game::GOOMBA)), game(game) , frame(0), frameRunner(0), previousOffset(0), frozen(true), velocity(2), ended(false)
{
	string line;

	getline(atributes, line);

	stringstream lineStream(line);

	int posX, posY;
	lineStream >> posX;
	lineStream >> posY;

	position = Vector2D<int>((posX) * Game::TILE_SIDE, (posY-1) * Game::TILE_SIDE);
	direction = Vector2D<int>(-velocity, 0);
}

void
Goomba::render() const {

	if (!frozen) {
		//posición del goomba
		SDL_Rect GPosition;
		GPosition.x = position.getX();
		GPosition.y = position.getY();
		GPosition.w = Game::TILE_SIDE;
		GPosition.h = Game::TILE_SIDE;

		//Muerte del goomba en el hit con el frame 2

		//Renderizamos con los parametros actualizados
		goombaTexture->renderFrame(GPosition, 0, frame);
	}
}


void
Goomba::update() {

	//FUNCIONAL: Los goombas spawnean en su sitio cuando el jugador alcanza a verlos en la pantalla
	int mapOffset = game->getMapOffset();
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

		SDL_Rect GoombaRect = getRect();
		GoombaRect.y += direction.getY();
		GoombaRect.x += direction.getX();

		// CAMBIAR: Verifica colisión en todas las direcciones
		Collision collision = game->checkEnemyCollision(GoombaRect, false);

		//COLISION VERTICAL
		if (!collision.collides) {
			direction.setY(velocity);
			position.setY(newPosition.getY());
		}
		else {
			if (collision.intersection.y > position.getY()) {
				direction.setY(0);
			} //SUELO
			else if (collision.intersection.y < position.getY()) {
				direction.setY(velocity);
			} //TECHO
		}

		//RECALCULO DE LA COLISION
		GoombaRect.x += direction.getX();
		GoombaRect.y = position.getY();

		collision = game->checkEnemyCollision(GoombaRect, false);

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
			cout << "Goomba: Me he morido por limite de mapa" << endl;
		}
	}

	//FUNCIONAL: Los goombas se mueven en funcion el offset del mapa y su posición
	int newOffset = game->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}
}

Collision
Goomba::hit(const SDL_Rect& rect, bool fromPlayer) {

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
			colisionPlayer.damages = false;
			colisionPlayer.intersection = intersection;
			if (colisionPlayer.intersection.y < position.getY() + Game::TILE_SIDE / 2) {
				frame = 2;
				ended = true;
			}
			return colisionPlayer;
		}
		return colisionPlayer;
	}
	else {
		return game->checkPlayerCollision(rect, fromPlayer);
	}
 
}

SDL_Rect
Goomba::getRect() const {
	SDL_Rect GoombaRect;
	GoombaRect.x = position.getX() + game->getMapOffset();
	GoombaRect.y = position.getY();
	GoombaRect.w = Game::TILE_SIDE;
	GoombaRect.h = Game::TILE_SIDE;
	return GoombaRect;
}