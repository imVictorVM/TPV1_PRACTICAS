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
	if (getline(atributes,line)) {
		
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
		position = Vector2D<int>(positionx,positiony);
		vidas = nvidas;
		
	}
}

void
Player::render() const {
	SDL_Rect rect;
	rect.w = Game::TILE_SIDE;
	rect.h = Game::TILE_SIDE;

	int fy = 0, fx = 0;
	TexturePlayer->renderFrame(rect, fy, fx);
}

void
Player::update() {

}

void
Player::hit() {

}

void Player::HandleEvent() {

}

