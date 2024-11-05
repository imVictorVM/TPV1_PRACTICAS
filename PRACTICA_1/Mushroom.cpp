#include "Mushroom.h"
#include "Game.h"

using namespace std;

Mushroom::Mushroom(Game* game, int posX, int posY) : position(), mushroomTexture(game->getTexture(Game::MUSHROOM)), mushroomGame(game)
{
	//posicion de la seta
	position = Vector2D<int>(posX * Game::TILE_SIDE, posY * Game::TILE_SIDE);
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

Collision
hit(const SDL_Rect rect, bool fromPlayer) {

}