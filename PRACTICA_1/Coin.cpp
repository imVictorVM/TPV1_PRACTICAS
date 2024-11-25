#include "Coin.h"
#include "checkML.h"
#include "Game.h"
#include <fstream>
#include <vector>

using namespace std;

Coin::Coin(Game* game, std::istream& atributes) : Pickable(game) {
	string line;

	getline(atributes, line);

	stringstream lineStream(line);

	int posX, posY;
	lineStream >> posX;
	lineStream >> posY;

	position = Vector2D<int>((posX)*Game::TILE_SIDE, (posY-1)*Game::TILE_SIDE);
	direction = Vector2D<int>(0, 0);
	texture = gamePointer->getTexture(Game::COIN);

}

Coin::~Coin()
{
}

void
Coin::update() {

	int newOffset = gamePointer->getMapOffset();

	if (position.getX() < newOffset + Game::WINDOW_WIDTH * Game::TILE_SIDE) {
		frozen = false;
	}

	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}

	if (frameRunner == 0 || frameRunner > 3) frame = 0;
	if (frameRunner == 1) frame = 1;
	if (frameRunner == 2) frame = 2;
	if (frameRunner == 3) frame = 3;
	if (frameRunner > 3) frameRunner = 0;
	frameRunner++;
}

//Collision
//Coin::hit(const SDL_Rect& rect, bool fromPlayer) {
//
//	Collision colisionPlayer = { false,false,{0,0,0,0} };
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
//			colisionPlayer.collides = true;
//			colisionPlayer.intersection = intersection;
//			ended = true;
//			return colisionPlayer;
//		}
//		return colisionPlayer;
//	}
//	return colisionPlayer;
//
//}
//
//SDL_Rect
//Coin::getRect() const {
//	SDL_Rect CPosition;
//	CPosition.x = position.getX() + gamePointer->getMapOffset();
//	CPosition.y = position.getY();
//	CPosition.w = Game::TILE_SIDE;
//	CPosition.h = Game::TILE_SIDE;
//	return CPosition;
//}
//
//bool
//Coin::isAlive() const {
//	return !ended;
//}


