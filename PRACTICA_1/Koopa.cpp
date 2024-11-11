#include "Koopa.h"
#include "Game.h"

using namespace std;

Koopa::Koopa(Game* game, stringstream& atributes) : position(), koopaTexture(game->getTexture(Game::KOOPA)), koopaGame(game), frameRunner(0), frozen(true)
{
	string line;

	getline(atributes, line);

	stringstream lineStream(line);

	int posX, posY;
	lineStream >> posX;
	lineStream >> posY;

	position = Vector2D<int>(posX * Game::TILE_SIDE, posY * Game::TILE_SIDE);


}

void
Koopa::render() const {

	if (!frozen) {
		//posición del koopa
		SDL_Rect KPosition;
		KPosition.x = position.getX();
		KPosition.y = position.getY();
		KPosition.w = Game::TILE_SIDE;
		KPosition.h = Game::TILE_SIDE;

		int frame = 0;
		//movimiento del koopa
		if (frameRunner == 0) frame = 0;
		if (frameRunner == 1) frame = 1;
		if (frameRunner == 2) frame = 2;
		if (frameRunner == 3) frame = 3;


		//Renderizamos con los parametros actualizados
		koopaTexture->renderFrame(KPosition, 0, frame);
	}
}


void
Koopa::update() {


	if (!frozen) {
		if (frameRunner > 3) frameRunner = 0;
		frameRunner++;
	}
}

//Collision
//hit(const SDL_Rect rect, bool fromPlayer) {
//
//}