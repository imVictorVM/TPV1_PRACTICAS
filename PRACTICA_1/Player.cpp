#include "Player.h"
#include "Block.h"
#include "TileMap.h"
#include "Game.h"
#include "Collision.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

Player::Player(Game* game, stringstream& atributes) : position(), TexturePlayer(game->getTexture(Game::MARIANO)), GamePlayer(game), vidas(0), GroundPosition(), jump(false), frameRunner(0), leftLimit(){
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
	//Aplicamos numero de vidas con el tercer parametro
	int nvidas;
	lineStream >> nvidas;

	//Pasamos los parametros al constructor del player despues de leerlos
	position = Vector2D<int>(positionx * Game::TILE_SIDE, positiony * Game::TILE_SIDE);
	vidas = nvidas;
	lookingLeft = false;
}

void
Player::render() const {
	SDL_Rect MPosition;
	MPosition.x = position.getX();
	MPosition.y = position.getY();
	MPosition.w = Game::TILE_SIDE;
	MPosition.h = Game::TILE_SIDE;

	int frame;
	//Si el jugador esta saltando ponemos el frame 6
	if (!jump) frame = 6;
	//elegimos el frame de movimiento del jugador en funcion del valor de frameRunner, si esta quieto se descarta por la siguiente condicional
	else {
		if (frameRunner == 0) frame = 0;
		else if (frameRunner == 1) frame = 2;
		else if (frameRunner == 2) frame = 3;
		else frame = 4;
	}
	//Si el jugador esta quieto en horizontal y puede saltar ponemos el frame 0
	if (direction.getX() == 0 && jump) frame = 0;


	//Si recibe daño ponemos el frame 1
	SDL_Rect rect;
	bool fromPlayer = false;
	Collision colision = hit(rect,fromPlayer);
	if (hit(rect,fromPlayer)) frame = 1;

	//Esto es para comprobar si esta mirando a la izquierda o a la derecha y en funcion de eso girar el render en funcion de donde mire
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	/*if (direction.getX() < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}*/
	if (lookingLeft) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	//Renderizamos con los parametros actualizados
	TexturePlayer->renderFrame(MPosition, 0, frame, flip);

}

void
Player::update() {

	Vector2D<int> newPosition = position + direction;
	leftLimit = false;

	//Si el jugador esta en el medio de la pantalla el offset avanza y solo funciona la direccion vertical del player
	if (position.getX() > Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 && direction.getX() > 0) {
		GamePlayer->setMapOffset(Game::TILE_SIDE/2);
		position = Vector2D<int>(Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 + 16, newPosition.getY());
	} //Si el jugador esta en el borde izquierdo de la pantalla mantenemos su posicion aunque pulsemos la tecla
	else if (position.getX() < 0) {
		leftLimit = true;
		position = Vector2D<int>(0, newPosition.getY());
	} //Si esta entre los dos limites funciona de manera normal
	else position = newPosition;

	//NOTA IMPORTANTE, si se detecta por bloques cambiar lo comentado y descomentado
	if (GroundCollision()) {

		//Si hay que hacer pruebas usar este codigo para mantener el suelo y comentar lo siguiente
		position = Vector2D<int>(position.getX(), 416);

		//Si hay que probar la colision de tiles descomentar esto y comentar lo anterior
		//direction = Vector2D<int>(direction.getX(), 0);
		//GroundPosition = GroundPosition;
		//position = Vector2D<int>(position.getX(), GroundPosition);
	}

	//Si el jugador esta por debajo del limite de salto y esta en el suelo o esta tocando un bloque por encima activamos la capacidad de saltar
	if (position.getY() >= GroundPosition - 100 && GroundCollision() || BlockCollision()) jump = true;
	//Si el jugador esta por encima del limite de salto o no esta en el suelo desactivamos la capacidad de saltar
	else jump = false;

	//Si colisionamos el bloque mantenemos la posicion y activamos saltar (creo que es redundante)
	if (BlockCollision()) {
		position = Vector2D<int>(position.getX(), position.getY());
		jump = true;
	}
		
	//Actualizamos el frame de correr siempre, el render del jugador se encarga de usar esto en caso de movimiento
	if (frameRunner > 3) frameRunner = 0;
	frameRunner++;

	//Esto es para perder vidas si se sale del mapa o es golpeado por un enemigo
	if (hit()) {
		vidas--;
	}

}

bool
Player::GroundCollision() {

	//NOTA IMPORTANTE
	//Esta es la logica de los tiles, detectamos el tile que esta justo debajo del jugador con GamePlayer->GetTile();
	//Si el valor del tile es alguno con los que tiene que colisionar, entre ellos el bloque normal del suelo (36), el jugador mantiene su eje Y en el groundPosition
	//Es necesario modificar el groundCollision y el update del jugador que usa el GroundCollision para probar esta lógica.
	
	//ERROR: A la hora de recalcular el groundPosition se clipea el jugador y atraviesa el suelo una vez, haciendo que se pase de los limites de la matriz.

	//Si hay que probar la colision de tiles descomentar esto y comentar lo siguiente

	//int valor = GamePlayer->getTile();
	//if (valor == 1 || valor == 2 || valor == 3 || valor == 10 || valor == 11 || valor == 12 ||
	//	valor == 18 || valor == 19 || valor == 20 || valor == 21 || valor == 27 || valor == 28 ||
	//	valor == 29 || valor == 30 || valor == 36 || valor == 37 || valor == 38 || valor == 39 ||
	//	valor == 46 || valor == 47 || valor == 48 || valor == 55 || valor == 56 || valor == 57)
	//{
	//	GroundPosition = position.getY();
	//	return true;
	//}
	//else return false;


	//Si hay que hacer pruebas usar este codigo para mantener el suelo y comentar lo anterior

	if (position.getY() >= 416) {
		GroundPosition = position.getY();
		return true;
	}	
	return false;
}

bool
Player::BlockCollision() {
	GroundPosition = position.getY();
	for (Block* block : GamePlayer->getBlocks()) { // Debes tener un método que devuelva todos los bloques
		SDL_Rect blockRect = block->getRect();

		// Crear el rectángulo del jugador
		SDL_Rect playerRect;
		playerRect.x = position.getX();
		playerRect.y = position.getY();
		playerRect.w = Game::TILE_SIDE;
		playerRect.h = Game::TILE_SIDE;

		// Comprobar si hay una intersección
		if (SDL_HasIntersection(&playerRect, &blockRect)) {
			// Verificar que el jugador esté aterrizando sobre el bloque
			if (playerRect.y + playerRect.h <= blockRect.y + blockRect.h && playerRect.y + playerRect.h >= blockRect.y) {
				GroundPosition = blockRect.y; // El jugador aterriza en el bloque
				Vector2D<int> newPosition = Vector2D<int>(position.getX(), GroundPosition - playerRect.h);
				position = newPosition; // Ajustar la posición del jugador a la parte superior del bloque
				return true;
			}
			direction = Vector2D<int>(direction.getX(), 0);
			return false;
		}

		if (block->hit(position)) {
			return true;
		}
	}
	return false;
}

//Mirar player.h
Collision hit(const SDL_Rect& rect, bool fromPlayer) {
	return GamePlayer->CheckCollisions(rect,fromPlayer);
}

void Player::HandleEvent(SDL_Event event) {
	//La direccion tambien cuenta como si fuese la velocidad, uso tileside por ser una variable global y accesible para todos
	switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			if (event.type == SDL_KEYDOWN) 
				direction = Vector2D<int>(1 * Game::TILE_SIDE / 2, direction.getY());
			else if (event.type == SDL_KEYUP) 
				direction = Vector2D<int>(0, direction.getY());
			lookingLeft = false;
			break;
		case SDLK_LEFT: 
			if (!leftLimit)
				direction = Vector2D<int>(-1 * Game::TILE_SIDE / 2, direction.getY());
			else if (event.type == SDL_KEYUP || leftLimit) 
				direction = Vector2D<int>(0, direction.getY());
			lookingLeft = true;
			break;
		case SDLK_UP:
			if (jump) {
				direction = Vector2D<int>(direction.getX(), -1 * Game::TILE_SIDE / 2);
			}
			else if (event.type == SDL_KEYUP || !jump)
				direction = Vector2D<int>(direction.getX(), Game::TILE_SIDE);
			break;
		default:
			direction = Vector2D<int>(direction.getX(), direction.getY());
			break;
	}
	if (event.type == SDL_KEYUP) direction = Vector2D<int>(0, Game::TILE_SIDE);
}

//Obtenemos la posicion para la colision
Vector2D<int> Player::getPosition() const {
	return position;
}

//Obtenemos la direccion para la colision de bloques cuando mario salta desde abajo
Vector2D<int> Player::getDirection() const {
	return direction;
}

//Recordemos que el rect del jugador tiene el origen distinto al de los tiles para colisionar con el entorno, por eso puede atravesarlos
SDL_Rect Player::getRect() const {
	SDL_Rect playerRect;
	playerRect.x = position.getX();
	playerRect.y = position.getY();
	playerRect.w = Game::TILE_SIDE;
	playerRect.h = Game::TILE_SIDE;
	return playerRect;
}