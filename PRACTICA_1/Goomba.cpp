#include "Goomba.h"
#include "Game.h"

using namespace std;

Goomba::Goomba(Game* game, stringstream& atributes) : position(), goombaTexture(game->getTexture(Game::GOOMBA)), goombaGame(game) , frameRunner(0)
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
Goomba::render() const {
	//posición del goomba
	SDL_Rect GPosition;
	GPosition.x = position.getX();
	GPosition.y = position.getY();
	GPosition.w = Game::TILE_SIDE;
	GPosition.h = Game::TILE_SIDE;

	int frame;
	//movimiento del goomba
	if (frameRunner == 0) frame = 0;
	if (frameRunner == 1) frame = 1;
	//muerte del goomba
	//if(condicion muerte del goomba) frame = 2;


	//Renderizamos con los parametros actualizados
	goombaTexture->renderFrame(GPosition, 0, frame);

}


void
Goomba::update() {

	if (frameRunner > 1) frameRunner = 0;
	frameRunner++;
}