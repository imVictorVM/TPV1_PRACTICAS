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
	Texture* TexturePlayer;
	Game* GamePlayer;
	int vidas;

public:

	Player(Game* game,std::stringstream& atributos);

	void render() const;

	void update();

	void hit();

	void HandleEvent();

};

