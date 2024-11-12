#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"
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
	int groundPositionY;
	Vector2D<int> direction;
	Texture* TexturePlayer;
	Game* GamePlayer;
	int vidas;
	bool jump; //Sirve para ver si podemos saltar o no
	int frameRunner; //Sirve como contador para saltar entre los frames 0,2,3
	bool leftLimit; //Sirve para no avanzar fuera de la pantalla a la izquierda
	bool lookingLeft; //para ver si está mirando a izquierda o derecha
	int damageCooldown; //tiempo de cooldown para el daño 
	int InitialPositionX;
	int InitialPositionY; 
	int velocity;
	
public:

	Player(Game* game,std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void HandleEvent(SDL_Event event);

	Vector2D<int> getPosition() const;
	
	Vector2D<int> ResetPosition() const;

	Vector2D<int> getDirection() const;

	//bool BlockCollision();

	SDL_Rect getRect() const;

	int getVidas() const;

};

