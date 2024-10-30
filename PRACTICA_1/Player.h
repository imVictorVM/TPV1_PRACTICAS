#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>

class Game;

class Player
{
protected:
	Vector2D<int> position;
	Vector2D<int> direction;
	Texture* TexturePlayer;
	Game* GamePlayer;
	int vidas;
	int GroundPosition; //Sirve para tener la altura previa a cuando hemos saltado
	bool jump; //Sirve para ver si podemos saltar o no
	int frameRunner; //Sirve como contador para saltar entre los frames 0,2,3
	bool leftLimit; //Sirve para no avanzar fuera de la pantalla a la izquierda
public:

	Player(Game* game,std::stringstream& atributos);

	void render() const;

	void update();

	bool GroundCollision();

	void hit();

	void HandleEvent(SDL_Event event);

};

