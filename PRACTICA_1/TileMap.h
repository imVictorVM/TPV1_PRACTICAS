#pragma once

#include "SceneObject.h"

#include <iostream>

#include <vector>


class Game;

class TileMap : public SceneObject
{

	std::vector<std::vector<int>> matriz;

public:
	TileMap(const std::string& mapa, Game* game);

	void render() const override;

	void update();

	Collision hit(const SDL_Rect& rect, bool fromPlayer);
};

