#pragma once

#include "SceneObject.h"


#include <fstream>
#include <iostream>
#include <string>

class Game;

class Player : public SceneObject
{
protected:

	//Vector2D<int> position;
	int groundPositionY;
	//Vector2D<int> direction;
	//Texture* TextureMario;
	Texture* TextureSuperMario;
	//Game* GamePlayer;
	int vidas;
	bool jump; //Sirve para ver si podemos saltar o no
	//int frameRunner; //Sirve como contador para saltar entre los frames 0,2,3
	bool leftLimit; //Sirve para no avanzar fuera de la pantalla a la izquierda
	bool lookingLeft; //para ver si está mirando a izquierda o derecha
	int damageCooldown; //tiempo de cooldown para el daño 
	int InitialPositionX;
	int InitialPositionY; 
	//int velocity;
	bool SuperMario;
public:

	Player(Game* game,std::stringstream& atributos);

	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void HandleEvent(SDL_Event event);

	Vector2D<int> getPosition() const;
	
	Vector2D<int> ResetPosition() const;

	Vector2D<int> getDirection() const;

	SDL_Rect getRect() const;

	int getVidas() const;

	void TransformacionSuperMario();

	void TransformacionMario();

	bool IsSuperMario() const;
};

