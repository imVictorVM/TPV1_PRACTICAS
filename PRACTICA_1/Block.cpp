#include "Block.h"
#include "Game.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

Block::Block(Game* game, stringstream& atributes) : position(), TextureBlock(game->getTexture(Game::BLOCK)), game(game), frameBlock(0), previousOffset(0) {
	string line;

	//Leemos la linea y pasamos los valores de atributos al string line, atributes se desecha
	getline(atributes, line);

	//Al estar atributes vacio necesitamos llamar a un nuevo stringstream que vaya leyendo los valores de uno en uno
	stringstream lineStream(line);

	//Aplicamos posicion en x con el primer parametro
	int positionx;
	lineStream >> positionx;
	//Aplicamos posicion en y con el segundo parametro
	int positiony;
	lineStream >> positiony;
	//Aplicamos tipo con el tercer parametro
	char T;
	lineStream >> T;
	//Aplicamos accion al golpearlo con el cuarto parametro
	char A;
	lineStream >> A;

	//Pasamos los parametros al constructor del player despues de leerlos
	position = Vector2D<int>(positionx * Game::TILE_SIDE, positiony * Game::TILE_SIDE);
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
}

//Misma logica que el jugador pero adaptado para los bloques en cuanto a los frames dependiendo de su tipo tambien
void
Block::render() const {
	SDL_Rect BPosition;
	BPosition.x = position.getX();
	BPosition.y = position.getY();
	BPosition.w = Game::TILE_SIDE;
	BPosition.h = Game::TILE_SIDE;

	int frame = 0;
	if (type == surprise) {
		if (frameBlock >= 0 && frameBlock < 3) frame = 0;
		else if (frameBlock >= 3 && frameBlock < 5) frame = 1;
		else if (frameBlock >= 5 && frameBlock < 7) frame = 2;
		else frame = 3;
	}
	else if (type == normal) {
		frame = 5;
	}
	else if (type == empty) {
		frame = 4;
	}

	TextureBlock->renderFrame(BPosition, 0, frame);
}

void
Block::update() {

	//Los bloques se mueven en funcion el offset del mapa
	int newOffset = game->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position = Vector2D<int>(position.getX() - offsetChange, position.getY());
		previousOffset = newOffset;
	}

	// Verifica la colisión con el jugador y actualiza el bloque si es necesario
	Vector2D<int> playerPosition = game->getPlayerPosition();
	if (hit(playerPosition)) {
		type = empty; 
	}

	//Actualizamos el frame del bloque siempre en caso de ser un bloque sorpresa, hay muchos frameBlocks para que sea lenta la trancision de un sprite a otro
	frameBlock++;
	if (frameBlock > 8) frameBlock = 0;
}

bool
Block::hit(Vector2D<int> playerPosition) {

	// Creamos un rect del bloque para compararlo con el del jugador
	SDL_Rect blockRect;
	blockRect.x = position.getX();
	blockRect.y = position.getY();
	blockRect.w = Game::TILE_SIDE;
	blockRect.h = Game::TILE_SIDE;

	// Creamos un rect del jugador para compararlo con el del bloque
	SDL_Rect playerRect;
	playerRect.x = playerPosition.getX();
	playerRect.y = playerPosition.getY();
	playerRect.w = Game::TILE_SIDE;
	playerRect.h = Game::TILE_SIDE;

	// Verificar si el jugador está justo debajo del bloque
	bool isBelow = playerRect.y > blockRect.y + blockRect.h;  //El eje y del jugador es mayor que el eje y del bloque // Por debajo en el eje y (Vector y mayor)

	// El eje x del jugador + la dimension x del jugador > el eje x del bloque
	// El eje x del jugador < el eje x del bloque + la dimension del bloque 
	bool isAlignedHorizontally = playerRect.x + playerRect.w > blockRect.x && playerRect.x < blockRect.x + blockRect.w; // Centrado en el eje x
	
	// Verificamos la direccion del jugador
	Vector2D<int> direction = game->getPlayerDirection();
	bool isMovingUp = direction.getY() < 0;  //El jugador esta saltando hacia arriba

	//Verificamos la distancia
	int distance = playerRect.y - blockRect.y + blockRect.h; //Distancia entre el jugador y el bloque
	int MinDistance = Game::TILE_SIDE * 2 + Game::TILE_SIDE / 2; //Distancia minimo para que la colision se produzca (Calculo a mano)

	// Usar SDL_HasIntersection para verificar colisión
	return isBelow && isAlignedHorizontally && isMovingUp && distance <= MinDistance;
}

//Obtenemos el bloque para que el jugador lo compare a la hora de posarse encima
SDL_Rect Block::getRect() const {
    SDL_Rect blockRect;
    blockRect.x = position.getX();
    blockRect.y = position.getY();
    blockRect.w = Game::TILE_SIDE;
    blockRect.h = Game::TILE_SIDE;
    return blockRect;
}