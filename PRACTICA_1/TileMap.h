#pragma once
#include <SDL.h>
#include <iostream>
#include "Texture.h"
#include "Vector2D.h"
#include <vector>
//#include "Game.h"

class Game;

class TileMap
{
	Game* game;
	Texture* patrones;

	std::vector<std::vector<int>> matriz;

public:
	TileMap(const std::string& mapa, Game* game);


	void render() const;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	int tileRect(Vector2D<int> playerPosition);
};

