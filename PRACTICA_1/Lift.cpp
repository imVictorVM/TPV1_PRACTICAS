#include "checkML.h"
#include "Lift.h"
#include "Game.h"


using namespace std;

Lift::Lift(Game* game, istream& atributes) : SceneObject(game, atributes) {
	
	string line;

	getline(atributes, line);

	stringstream lineStream(line);

	lineStream >> velocity;

	width = Game::TILE_SIDE * 3;
	height = Game::TILE_SIDE / 2;
	texture = gamePointer->getTexture(Game::LIFT);
	

}

Lift::~Lift()
{
}



void
Lift::update() {

	int newOffset = gamePointer->getMapOffset();

	if (position.getX() < newOffset + Game::WINDOW_WIDTH * Game::TILE_SIDE) {
		frozen = false;
	}
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}

	if (!frozen) {
		Vector2D<int> newPosition = position + direction;
		position.setY(newPosition.getY());
		if (position.getY() < 0) {
			position.setY(500);
		}
		else if (position.getY() > 500) {
			position.setY(0);
		}
	}
}

Collision
Lift::hit(const SDL_Rect& rect, bool fromPlayer) {

	Collision colisionPlayer = { false,false,{0,0,0,0} };
	if (fromPlayer) {
		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect LiftRect;
		LiftRect = getRect();
		LiftRect.x += gamePointer->getMapOffset();

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &LiftRect, &intersection)) {
			
			colisionPlayer.collides = true;
			colisionPlayer.intersection = intersection;
			cout << "COLISIONO" << endl;
			//if (intersection.w > intersection.h) { //Vertical
			//	colisionPlayer.collides = true;
			//}
			//else { //Horizontal
			//	colisionPlayer.collides = true;
			//}
			return colisionPlayer;
		}
		return colisionPlayer;
	}
	return colisionPlayer;

}


