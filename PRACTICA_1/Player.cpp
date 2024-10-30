#include "Player.h"
#include "Game.h"
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
	if (hit()) frame = 1;

	//Esto es para comprobar si esta mirando a la izquierda o a la derecha y en funcion de eso girar el render en funcion de donde mire
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (direction.getX() < 0) {
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

	//Si el jugador pisa suelo a cierta altura, su eje Y se mantendrá - CAMBIAR POR COLISION DE BLOQUE
	if (GroundCollision()) {
		position = Vector2D<int>(position.getX(), 416);
	}
		
	//Si el jugador esta por debajo del limite de salto y esta en el suelo activamos la capacidad de saltar
	if (position.getY() >= GroundPosition - 100 && GroundCollision()) jump = true;
	//Si el jugador esta por encima del limite de salto o no esta en el suelo desactivamos la capacidad de saltar
	else jump = false;

	//Actualizamos el frame de correr siempre, el render del jugador se encarga de usar esto en caso de movimiento
	if (frameRunner > 3) frameRunner = 0;
	frameRunner++;

	//if (position.getX() < Game::TILE_SIDE / 2) leftLimit = true;
	//else leftLimit = false;

	//DEBUG
	std::cout << "Position -> X: " << position.getX() << ", Y: " << position.getY() << std::endl;
	std::cout << "GroundCollision: " << GroundCollision() << std::endl;
	std::cout << "GroundTimer: " << GroundPosition << std::endl;
}

bool
Player::GroundCollision() {
	//Si la posicion es la del suelo guardamos esa posicion por si queremos saltar y retornamos true
	if (position.getY() >= 416) {
		GroundPosition = position.getY();
		return true;
	}
	else return false;
		
}

//Mirar player.h
bool
Player::hit() const {
	return false;
}

void Player::HandleEvent(SDL_Event event) {
	//La direccion tambien cuenta como si fuese la velocidad, uso tileside por ser una variable global y accesible para todos
	switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			if (event.type == SDL_KEYDOWN) 
				direction = Vector2D<int>(1 * Game::TILE_SIDE / 2, direction.getY());
			else if (event.type == SDL_KEYUP) 
				direction = Vector2D<int>(0, direction.getY());
			break;
		case SDLK_LEFT: 
			if (!leftLimit)
				direction = Vector2D<int>(-1 * Game::TILE_SIDE / 2, direction.getY());
			else if (event.type == SDL_KEYUP || leftLimit) 
				direction = Vector2D<int>(0, direction.getY());
			break;
		case SDLK_UP:
			if (jump) {
				direction = Vector2D<int>(direction.getX(), -1 * Game::TILE_SIDE / 2);
			}
			else if (event.type == SDL_KEYUP || !jump )
				direction = Vector2D<int>(direction.getX(), Game::TILE_SIDE);
			break;
		default:
			direction = Vector2D<int>(direction.getX(), direction.getY());
			break;
	}
	if (event.type == SDL_KEYUP) direction = Vector2D<int>(0, Game::TILE_SIDE);
}
