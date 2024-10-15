#pragma once
#include <SDL.h>
#include <iostream>
#include "Texture.h"
#include <vector>

class TileMap
{
	Texture* patrones;

	std::vector<std::vector<int>> matriz;

public:
	TileMap(std::string mapa);


	void render() const;

	void update();

	void hit();

};

