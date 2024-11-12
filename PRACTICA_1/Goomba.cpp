#include "checkML.h"
#include "Goomba.h"
#include "Game.h"

using namespace std;

Goomba::Goomba(Game* game, stringstream& atributes) : position(), goombaTexture(game->getTexture(Game::GOOMBA)), game(game) , frame(0), frameRunner(0), previousOffset(0), frozen(true)
{
	string line;

	getline(atributes, line);

	stringstream lineStream(line);

	int posX, posY;
	lineStream >> posX;
	lineStream >> posY;

	position = Vector2D<int>((posX-1) * Game::TILE_SIDE, (posY-1) * Game::TILE_SIDE);
	direction = Vector2D<int>(-1, 0);
	notGround = Vector2D<int>(0, 1);
	
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

		//muerte del goomba
		//if(condicion muerte del goomba) frame = 2;


		//Renderizamos con los parametros actualizados
		goombaTexture->renderFrame(GPosition, 0, frame);
	}
}


void
Goomba::update() {
	
	int mapOffset = game->getMapOffset();
	if (position.getX() < mapOffset + game->WINDOW_WIDTH) frozen = false;
	

	if (!frozen) {
		if (!groundCollision()) {
			position = position + notGround;
		}
		position = position + direction;
		if (frameRunner == 0) frame = 0;
		if (frameRunner == 1) frame = 1;

		if (frameRunner > 1) frameRunner = 0;
		else frameRunner++;

	}

	//Los goombas se mueven en funcion el offset del mapa
	int newOffset = game->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position = Vector2D<int>(position.getX() - offsetChange, position.getY());
		previousOffset = newOffset;
	}

	// Verifica la colisión con el jugador y actualiza el bloque si es necesario
	/*Vector2D<int> playerPosition = game->getPlayerPosition();
	if (game->checkPlayerCollision(getRect(), true).collides) {
		type = empty;
	}*/

	//Actualizamos el frame del bloque siempre en caso de ser un bloque sorpresa, hay muchos frameBlocks para que sea lenta la trancision de un sprite a otro
	/*frameBlock++;
	if (frameBlock > 8) frameBlock = 0;*/


}
bool
Goomba::groundCollision() {
	return false;
}

//Collision
//hit(const SDL_Rect rect, bool fromPlayer) {
//
//}