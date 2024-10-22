#pragma once
#include <SDL.h>
#include <iostream>
#include "Texture.h"
#include <vector>
#include "Game.h"

class TileMap
{
	Game* game;
	Texture* patrones;

	std::vector<std::vector<int>> matriz;

public:
	TileMap(const std::string& mapa, Game* game);


	void render() const;

	void update();

	void hit();

};

