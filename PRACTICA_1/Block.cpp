#include "checkML.h"
#include "Block.h"
#include "Game.h"

#include "Mushroom.h"
#include "Player.h"
#include <fstream>

#include <string>
using namespace std;

Block::Block(Game* game, istream& atributes) : SceneObject(game, atributes)
	 //position(), TextureBlock(game->getTexture(Game::BLOCK)), action(), gamePointer(game), frameBlock(0), previousOffset(0), object(false), ended(false)
	 {
	texture = game->getTexture(Game::BLOCK); 
	object = false;
	string line;

	//Leemos la linea y pasamos los valores de atributos al string line, atributes se desecha
	getline(atributes, line);

	//Al estar atributes vacio necesitamos llamar a un nuevo stringstream que vaya leyendo los valores de uno en uno
	stringstream lineStream(line);

	//Aplicamos posicion en x con el primer parametro
	//int positionx;
	//lineStream >> positionx;
	////Aplicamos posicion en y con el segundo parametro
	//int positiony;
	//lineStream >> positiony;
	//Aplicamos tipo con el tercer parametro
	char T;
	lineStream >> T;
	//Aplicamos accion al golpearlo con el cuarto parametro
	char A;
	lineStream >> A;

	//Pasamos los parametros al constructor del player despues de leerlos
	//position = Vector2D<int>((positionx) * Game::TILE_SIDE, (positiony-1) * Game::TILE_SIDE);
	switch (T) {
		case '?': type = surprise;
			break;
		case 'B': type = normal;
			break;
		case 'H': type = hidden;
			break;
		default: type = empty;
			break;
	}
	switch (A) {
	case 'C': action = coin;
		break;
	case 'P': action = powerup;
		break;
	}

	frozen = false;
}

//Misma logica que el jugador pero adaptado para los bloques en cuanto a los frames dependiendo de su tipo tambien
//void
//Block::render() const {
//	
//	if (!ended) {
//		SDL_Rect BPosition;
//		BPosition.x = position.getX();
//		BPosition.y = position.getY();
//		BPosition.w = Game::TILE_SIDE;
//		BPosition.h = Game::TILE_SIDE;
//
//		
//
//		texture->renderFrame(BPosition, 0, frame);
//	}
//
//}

void
Block::update() {
	
	//Los bloques se mueven en funcion el offset del mapa
	int newOffset = gamePointer->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}


	if (type == surprise) {
		if (frameRunner >= 0 && frameRunner < 3) frame = 0;
		else if (frameRunner >= 3 && frameRunner < 5) frame = 1;
		else if (frameRunner >= 5 && frameRunner < 7) frame = 2;
		else frame = 3;
	}
	else if (type == normal) {
		frame = 5;
	}
	else if (type == empty) {
		frame = 4;
	}

	//Actualizamos el frame del bloque siempre en caso de ser un bloque sorpresa, hay muchos frameBlocks para que sea lenta la trancision de un sprite a otro
	frameRunner++;
	if (frameRunner > 7) frameRunner = 0;

}

Collision
Block::hit(const SDL_Rect& rect, bool fromPlayer) {

	

	Collision colision = { false,false,{0,0,0,0} };
	
	// Creamos un rect del bloque para compararlo con el del jugador
	SDL_Rect blockRect;
	blockRect.x = position.getX() + gamePointer->getMapOffset();
	blockRect.y = position.getY();
	blockRect.w = Game::TILE_SIDE;
	blockRect.h = Game::TILE_SIDE;

	// Creamos un rect del player tomando de valor el que le llega como argumento
	SDL_Rect playerRect;
	playerRect = rect;

	SDL_Rect intersection;
	if (SDL_IntersectRect(&playerRect, &blockRect, &intersection)) {
		colision.collides = true;
		colision.intersection = intersection;
		if (fromPlayer) {
			if (colision.intersection.y > position.getY() + Game::TILE_SIDE / 2) {
				
				if (type != empty) {
					if (type == normal && rect.h > Game::TILE_SIDE) ended = true; //MARIO GRANDE ROMPE BLOQUES
					else if (type == surprise || type == hidden) {
						if (action == powerup && !ObtainObject()) {
							//Logica de la aparición de la seta
							cout << "Seta" << endl;
							object = true;
						}
						if (action == coin) {
							//Logica de la aparición de la moneda, es solo para HUD
							cout << "Moneda" << endl;
						}
						type = empty;
					}
				}

			}
		}
		return colision;
	}
	return colision;
}

//Obtenemos el bloque para que el jugador lo compare a la hora de posarse encima
//SDL_Rect Block::getRect() const {
//    SDL_Rect blockRect;
//    blockRect.x = position.getX();
//    blockRect.y = position.getY();
//    blockRect.w = Game::TILE_SIDE;
//    blockRect.h = Game::TILE_SIDE;
//    return blockRect;
//}

bool Block::ObtainObject() {
	return object;
}

void Block::itemObtained() {
	object = false;
}

//bool Block::isAlive() const {
//	return !ended;
//}