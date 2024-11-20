#include "checkML.h"
#include "Mushroom.h"
#include "Game.h"

using namespace std;

Mushroom::Mushroom(Game* game, int posX, int posY) : position(), direction(), mushroomTexture(game->getTexture(Game::MUSHROOM)), mushroomGame(game), velocity(2)
{
	//posicion de la seta
	position = Vector2D<int>(posX, posY - Game::TILE_SIDE);
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
	Vector2D<int> newPosition = position + direction;
	
	position = newPosition;
}


Collision
Mushroom::hit(const SDL_Rect& rect, bool fromPlayer) {
	Collision colision = { false,false,{0,0,0,0} };

	if (fromPlayer) {
		// Creamos un rect del bloque para compararlo con el del jugador
		SDL_Rect MushRect;
		MushRect.x = position.getX() + mushroomGame->getMapOffset();
		MushRect.y = position.getY();
		MushRect.w = Game::TILE_SIDE;
		MushRect.h = Game::TILE_SIDE;

		// Creamos un rect del player tomando de valor el que le llega como argumento
		SDL_Rect playerRect;
		playerRect = rect;

		SDL_Rect intersection;
		if (SDL_IntersectRect(&playerRect, &MushRect, &intersection)) {
			colision.collides = true;
			colision.intersection = intersection;
			//Logica para hacer que mario sea grande
			return colision;
		}
		return colision;
	}
	return colision;
}