#include "Player.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

Player::Player(Game* game, stringstream& atributes) : position(), TexturePlayer(game->getTexture(Game::MARIANO)), GamePlayer(game), vidas(0){
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
	if (position.getX() % 3 == 0) frame = 0;
	else if (position.getX() % 3 == 1) frame = 2;
	else frame = 3;

	TexturePlayer->renderFrame(MPosition, 0, frame);

}

void
Player::update() {

	Vector2D<int> newPosition = position + direction;
	
	if (position.getX() > Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 && direction.getX() > 0) GamePlayer->setMapOffset(Game::TILE_SIDE);
	position = newPosition;

	if (Collision()) position = Vector2D<int>(position.getX(), 416);

	std::cout << "Position -> X: " << position.getX() << ", Y: " << position.getY() << std::endl;
}

void
Player::hit() {

}

bool
Player::Collision() {
	if (position.getY() > 416) return true;
	else return false;
}

void Player::HandleEvent(SDL_Event event) {
	int PreviousPosition = position.getY();

	switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			if (event.type == SDL_KEYDOWN) 
				direction = Vector2D<int>(1 * Game::TILE_SIDE / 2, direction.getY());
			else if (event.type == SDL_KEYUP) 
				direction = Vector2D<int>(0, direction.getY());
			break;
		case SDLK_LEFT: 
			if (event.type == SDL_KEYDOWN) 
				direction = Vector2D<int>(-1 * Game::TILE_SIDE/2, direction.getY());
			else if (event.type == SDL_KEYUP) 
				direction = Vector2D<int>(0, direction.getY());
			break;
		case SDLK_UP:
			if (event.type == SDL_KEYDOWN && position.getY() > PreviousPosition - 100)
				direction = Vector2D<int>(direction.getX(), -1 * Game::TILE_SIDE / 2);
			else if (event.type == SDL_KEYUP)
				direction = Vector2D<int>(direction.getX(), -1);
			break;
		default:
			direction = Vector2D<int>(direction.getX(), direction.getY());
			break;
	}
	if (event.type == SDL_KEYUP) direction = Vector2D<int>(direction.getX(), Game::TILE_SIDE);
}
